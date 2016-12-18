#include "motion.hpp"
#include "common/time.hpp"
#include "common/logger.hpp"

namespace game{

	MotionSystem::MotionSystem() : System(){
		Require<Transform, Motion>();
	}

	MotionSystem::~MotionSystem(){}

	void MotionSystem::OnUpdate(Entity e){
		Transform* transform = ecs::GetComponent<Transform>(e);
		Motion* motion = ecs::GetComponent<Motion>(e);

		if(motion->type == MotionType::SIMPLE){
			SimpleResolve(motion, transform);
		} else {
			ServoResolve(motion, transform);
		}
	}

	void MotionSystem::SimpleResolve(Motion* motion, Transform* transform){
		float dt = Time::GetPreviousDeltaTime();
		if(glm::length(motion->direction) != 0){
			transform->position += glm::normalize(motion->direction) * motion->target_speed * dt;
		} else {
			motion->target_speed = 0;
		}

		if(motion->target_speed != 0 && motion->friction != 0){
			motion->target_speed -= dt * motion->friction;
			motion->target_speed = std::max(0.f, motion->target_speed);
		}
	}

	void MotionSystem::ServoResolve(Motion* motion, Transform* transform){
		// Send messages to physic system
	}
}
