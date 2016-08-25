#include "simple_motion.hpp"
#include "component/transform.hpp"
#include "component/action/simple_motion.hpp"
#include "common/time.hpp"
#include "common/logger.hpp"

namespace game{

	SimpleMotionSystem::SimpleMotionSystem() : System(){
		Require<Transform, SimpleMotion>();
	}

	SimpleMotionSystem::~SimpleMotionSystem(){}

	void SimpleMotionSystem::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void SimpleMotionSystem::OnMessage(IntentMessage message){
		Entity e = message.dest;

		// Process motion here
		if(message.intent == Intent::WALK || message.intent == Intent::RUN){
			Transform* t = ecs::GetComponent<Transform>(e);
			SimpleMotion* s = ecs::GetComponent<SimpleMotion>(e);
			t->position += Time::GetPreviousDeltaTime() * s->speed * message.direction;
		}
	}

}
