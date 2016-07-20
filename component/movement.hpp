#ifndef GAME_COMPONENT_MOVEMENT_HPP
#define GAME_COMPONENT_MOVEMENT_HPP

#include "common/glm.hpp"

namespace game{

	struct Movement{
		glm::vec3 target_velocity;
		glm::vec3 max_acceleration;
		glm::vec3 max_deceleration;
		glm::vec3 max_force;

		Movement();
	};
}

#endif //GAME_COMPONENT_MOVEMENT_HPP
