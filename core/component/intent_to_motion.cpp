#include "intent_to_motion.hpp"
#include "motion.hpp"

namespace game{

	IntentToMotion::IntentToMotion() : Behavior(){
		this->motion = nullptr;
		this->run_speed = 8;
		this->walk_speed = 1;
	}

	IntentToMotion::IntentToMotion(GameObject* parent) : IntentToMotion(){
		if(parent){
			parent->AttachComponent(this);
			parent->RegisterToLocalBus((MessageHandler<IntentMessage>*)this);
		}
	}

	IntentToMotion::IntentToMotion(IntentToMotion* intent_to_motion) : IntentToMotion(){
		this->run_speed = intent_to_motion->run_speed;
		this->walk_speed = intent_to_motion->walk_speed;
	}

	IntentToMotion* IntentToMotion::Clone(){
		return new IntentToMotion(this);
	}

	void IntentToMotion::Update(){
		this->MessageHandler<IntentMessage>::UpdateMessages();
	}

	void IntentToMotion::NotifyNewComponentAdded(){
		if(!this->parent){ return; }
		this->motion = this->parent->GetComponent<Motion>();
	}

	void IntentToMotion::OnMessage(IntentMessage message){
		if(!this->motion){ return; }

		if(glm::length(message.direction) != 0){
			motion->direction = glm::normalize(message.direction);
		} else {
			motion->direction = glm::vec3(0.f, 0.f, 0.f);
		}

		switch(message.intent){
			case(Intent::WALK):
				motion->target_speed = this->walk_speed;
				break;
			case(Intent::RUN):
				motion->target_speed = this->run_speed;
				break;
			case(Intent::IDLE):
				motion->target_speed = 0.f;
				break;

			default:
				return;
		}
	}
}
