#ifndef GAME_COMPONENT_MOTION_HPP_
#define GAME_COMPONENT_MOTION_HPP_

#include "common/glm.hpp"

namespace game{

	enum class MotionType{SIMPLE, SERVO};

	struct Motion{
		MotionType type;
		float target_speed;
		float friction;
		glm::vec3 direction;

		Motion();
		Motion(float);
	};
}

#endif //GAME_COMPONENT_MOTION_HPP_
