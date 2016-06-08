#include "movement.hpp"
#include "entity/entity.hpp"

namespace game{

	Movement::Movement() : Component(){
		target_velocity = glm::vec3(0.f, 0.f, 0.f);
		max_acceleration = glm::vec3(0.f, 0.f, 0.f);
		max_deceleration = glm::vec3(0.f, 0.f, 0.f);
		max_force = glm::vec3(0.f, 0.f, 0.f);
	}

	Movement::Movement(unsigned long parent) : Movement(){
		Entity::AttachComponent<Movement>(parent, this);
	}

	Movement::Movement(Movement* movement){
		target_velocity = movement->target_velocity;
		max_acceleration = movement->max_acceleration;
		max_deceleration = movement->max_deceleration;
		max_force = movement->max_force;
	}

	Movement::~Movement(){}

	Movement* Movement::Clone(){
		return new Movement(this);
	}
}
