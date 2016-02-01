#include "input_to_motion.hpp"
#include "motion.hpp"

namespace game{

	InputToMotion::InputToMotion() : Component(){
		this->motion = nullptr;
	}

	InputToMotion::InputToMotion(GameObject* parent) : InputToMotion(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	InputToMotion::InputToMotion(InputToMotion* input_to_motion) : InputToMotion(){

	}

	InputToMotion* InputToMotion::Clone(){
		return new InputToMotion(this);
	}

	void InputToMotion::Update(){
		ProcessReceivedMessages();
	}

	void InputToMotion::NotifyNewComponentAdded(){
		if(!this->parent){ return; }
		this->motion = this->parent->GetComponent<Motion>();
	}

	void InputToMotion::ProcessReceivedMessages(){
		for(auto message : this->MessageHandler<InputMessage>::messages_){
			this->HandleKeyEvent(message);
		}
		this->MessageHandler<InputMessage>::messages_.clear();
	}

	void InputToMotion::HandleKeyEvent(InputMessage message){
		if(!this->motion){ return; }

		int modifier;
		message.status == KEY_PRESSED ? modifier = 1 : modifier = 0;
		motion->target_speed = 8;
		if(message.modifier_pressed){ motion->target_speed /= 2; }

		switch(message.command){
			case(Command::MOVE_UP):
				motion->direction.y = modifier;
				break;
			case(Command::MOVE_DOWN):
				motion->direction.y = -modifier;
				break;
			case(Command::MOVE_LEFT):
				motion->direction.x = -modifier;
				break;
			case(Command::MOVE_RIGHT):
				motion->direction.x = modifier;
				break;
			default:
				return;
		}
	}
}
