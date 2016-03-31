#ifndef GAME_COMPONENT_MOTION_TO_ANIMATION_HPP
#define GAME_COMPONENT_MOTION_TO_ANIMATION_HPP

#include "behavior.hpp"
#include "transform.hpp"
#include "common.hpp"

namespace game{

	struct MotionToAnimation : public Behavior{
		glm::vec3* velocity;
		glm::vec3 previous_velocity;

		// Helpers
		MotionToAnimation();
		MotionToAnimation(GameObject*);
		MotionToAnimation(MotionToAnimation*);
		~MotionToAnimation();
		virtual MotionToAnimation* Clone();
		virtual void Notify(SystemEvent);
		virtual void Update();
		Direction GetDirectionFromMotion();
	};
}

#endif //GAME_COMPONENT_MOTION_TO_ANIMATION_HPP
