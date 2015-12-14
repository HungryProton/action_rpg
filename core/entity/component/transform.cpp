#include <cstdlib>
#include <iostream>
#include "transform.hpp"

namespace game{
	Transform::Transform() : Component(){
		this->position = glm::vec3(0.f, 0.f, 0.f);
		this->rotation = glm::vec3(0.f, 0.f, 0.f);
		this->scale = glm::vec3(1.f, 1.f, 1.f);
		this->velocity = glm::vec3(0.f, 0.f, 0.f);
	}

	Transform::Transform(GameObject* p) : Transform(){
		p->AttachComponent(this);
	}

	Transform::Transform(Transform* transform){
		this->position = transform->position;
		this->rotation = transform->rotation;
		this->scale = transform->scale;
		this->velocity = transform->velocity;
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
