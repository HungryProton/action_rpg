#include "movement.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	Movement::Movement(){
		target_velocity = glm::vec3(0.f, 0.f, 0.f);
		max_acceleration = glm::vec3(0.f, 0.f, 0.f);
		max_deceleration = glm::vec3(0.f, 0.f, 0.f);
		max_force = glm::vec3(0.f, 0.f, 0.f);
	}
}
