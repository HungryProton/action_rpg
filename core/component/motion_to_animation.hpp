#ifndef GAME_COMPONENT_MOTION_TO_ANIMATION_HPP
#define GAME_COMPONENT_MOTION_TO_ANIMATION_HPP

#include "component.hpp"
#include "transform.hpp"
#include "common.hpp"

namespace game{

	struct MotionToAnimation : public Component{
		glm::vec3* velocity;
		glm::vec3 previous_velocity;

		// Helpers
		MotionToAnimation();
		MotionToAnimation(GameObject*);
		MotionToAnimation(MotionToAnimation*);
		~MotionToAnimation();
		virtual MotionToAnimation* Clone();
		virtual void NotifyNewComponentAdded();
		virtual void Update();
		Direction GetDirectionFromMotion();
	};
}

#endif //GAME_COMPONENT_MOTION_TO_ANIMATION_HPP
