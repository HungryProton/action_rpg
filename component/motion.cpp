#include "motion.hpp"

namespace game{

	Motion::Motion(){
		target_speed = 0;
		friction = 0.5;
		direction = glm::vec3(0.f, 0.f, 0.f);
		type = MotionType::SIMPLE;
	}

	Motion::Motion(float s) : Motion(){
		target_speed = s;
	}
}
