#ifndef GAME_COMPONENT_SIMPLE_MOTION_HPP_
#define GAME_COMPONENT_SIMPLE_MOTION_HPP_

#include "common/glm.hpp"

namespace game{

	struct SimpleMotion{
		float speed;

		SimpleMotion();
		SimpleMotion(float);
	};
}

#endif //GAME_COMPONENT_SIMPLE_MOTION_HPP_
