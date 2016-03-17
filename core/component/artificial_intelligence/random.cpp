#include "random.hpp"
#include "tools/time.hpp"
#include "tools/random.hpp"
#include "tools/utils.hpp"

namespace game{

	RandomAi::RandomAi() : Component(){
		timer = Time::GetCurrentTime();
		action_duration = 0;
	}

	RandomAi::RandomAi(GameObject* parent) : RandomAi(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	RandomAi::RandomAi(RandomAi* ai){
		this->timer = ai->timer;
		this->action_duration = ai->action_duration;
		this->intent = ai->intent;
	}

	RandomAi* RandomAi::Clone(){
		return new RandomAi(this);
	}

	void RandomAi::Update(){
		this->MessageHandler<EventMessage>::UpdateMessages();
		if(Time::GetCurrentTime() - timer >= action_duration){

			action_duration = 2.f + Random::NextFloat(4.f);
			timer = Time::GetCurrentTime();

			// 50% chances walking
			if(Random::NextInt(10) < 5){
				this->intent.direction.x = 1 - Random::NextInt(2);
				this->intent.direction.y = 1 - Random::NextInt(2);
				this->intent.direction.z = 0;

				this->intent.intent = Intent::WALK;
			} else {
				this->intent.intent = Intent::IDLE;
			}

			AttackIfNearbyEntity();
			ClearNearbyEntities();
		}


		this->parent->BroadcastLocally(this->intent);
	}

	void RandomAi::AttackIfNearbyEntity(){
		if(this->nearby_entities.size() == 0){ return; }
		if(Random::NextInt()%4 != 0){ return; }

		this->intent.intent = Intent::ATTACK;
		this->action_duration = 1.f;
	}

	void RandomAi::OnMessage(EventMessage msg){
		if(msg.type != EventType::ENTITY_EXISTS){ return; }
		if(msg.object == this->parent){ return; }

		float distance = Utils::Distance(msg.object, this->parent);
		if(distance == -1 || distance >= 1.f){ return; }

		this->nearby_entities.push_back(msg.object);
	}

	void RandomAi::ClearNearbyEntities(){
		this->nearby_entities.clear();
		return;

		auto it = this->nearby_entities.begin();
		while(it != this->nearby_entities.end()){
			Utils::Distance(this->parent, (*it)) >= 2 ? it = this->nearby_entities.erase(it) : it++;
		}
	}
}
