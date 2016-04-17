#include <cstdlib>
#include <iostream>
#include "entity/entity.hpp"
#include "transform.hpp"
#include "common/time.hpp"

namespace game{
	Transform::Transform() : Component(){
		this->position = glm::vec3(0.f, 0.f, 0.f);
		this->rotation = glm::vec3(0.f, 0.f, 0.f);
		this->scale = glm::vec3(1.f, 1.f, 1.f);
		this->velocity = glm::vec3(0.f, 0.f, 0.f);
		this->target_velocity = glm::vec3(0.f, 0.f, 0.f);
		this->previous_position = glm::vec3(0.f, 0.f, 0.f);
	}

	Transform::Transform(unsigned long id) : Transform(){
		Entity::AddComponent<Transform>(id, this);
	}

	Transform::Transform(Transform* transform) : Transform(){
		this->position = transform->position;
		this->rotation = transform->rotation;
		this->scale = transform->scale;
		this->velocity = transform->velocity;
		this->target_velocity = transform->target_velocity;
		this->previous_position = transform->previous_position;
	}

	Transform* Transform::Clone(){
		return new Transform(this);
	}

	void Transform::dbg_display(){
		std::cout << "x: " << this->position.x <<
					" y: " << this->position.y <<
					" z: " << this->position.z << std::endl;
	}
}
