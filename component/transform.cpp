#include <cstdlib>
#include <iostream>
#include "ecs/entity/entity.hpp"
#include "transform.hpp"
#include "common/time.hpp"

namespace game{


	Transform::Transform(){
		this->position = glm::vec3(0.f, 0.f, 0.f);
		this->rotation = glm::vec3(0.f, 0.f, 0.f);
		this->scale = glm::vec3(1.f, 1.f, 1.f);
		this->velocity = glm::vec3(0.f, 0.f, 0.f);
		this->previous_position = glm::vec3(0.f, 0.f, 0.f);
	}

	Transform::Transform(glm::vec3 pos) : Transform(){
		this->position = pos;
	}

	void Transform::dbg_display(){
		std::cout << "x: " << this->position.x <<
					" y: " << this->position.y <<
					" z: " << this->position.z <<
					" vx: " << this->velocity.x <<
					" vy: " << this->velocity.y <<
					" vz: " << this->velocity.z << std::endl;
	}
}
