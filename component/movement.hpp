#ifndef GAME_COMPONENT_MOVEMENT_HPP
#define GAME_COMPONENT_MOVEMENT_HPP

#include "component.hpp"
#include "common/glm.hpp"

namespace game{

	struct Movement : public Component{
		glm::vec3 target_velocity;
		glm::vec3 max_acceleration;
		glm::vec3 max_deceleration;
		glm::vec3 max_force;

		Movement();
		Movement(Entity);
		Movement(Movement*);
		virtual ~Movement();
		virtual Movement* Clone();
	};
}

#endif //GAME_COMPONENT_MOVEMENT_HPP
