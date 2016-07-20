#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "collider.hpp"
#include "ecs/entity/entity.hpp"
#include "messaging/concrete_messages/physic_intent.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	Collider::Collider(){
		this->gravity = 9.81f;
		this->sleeping = false;
		this->SetMass(1.f);
		this->restitution_factor = 0.8f;
		this->target_velocity = glm::vec3(0.f, 0.f, 0.f);
	}

	// TODO : Use the shape to determine object's volume and multiply by
	// material density to obtain mass
	void Collider::SetMass(float mass){
		this->mass = mass;
		this->weight = mass*this->gravity;
		if( mass > 0){
			this->inv_mass = 1.f / mass;
		} else {
			this->inv_mass = 0.f;
		}
	}
}

