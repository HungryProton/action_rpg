#include "random.hpp"
#include "tools/time.hpp"
#include "tools/random.hpp"

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
		this->action_duration = ai->timer;
		this->intent = ai->intent;
	}

	RandomAi* RandomAi::Clone(){
		return new RandomAi(this);
	}

	void RandomAi::Update(){
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
		}

		this->parent->BroadcastLocally(this->intent);
	}

}
