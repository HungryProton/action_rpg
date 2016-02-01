#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "collider.hpp"
#include "core/messaging/concrete_messages/physic_intent.hpp"
#include "core/messaging/message_bus.hpp"

namespace game{

	Collider::Collider() : shape_type(typeid(Collider)){
		this->gravity = 9.81f;
		this->sleeping = false;
		this->SetMass(1.f);
		this->restitution_factor = 0.8f;
	}

	Collider::Collider(GameObject* parent) : Collider(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Collider::Collider(Collider* collider) : Collider(){
		this->gravity = collider->gravity;
		this->sleeping = collider->sleeping;
		this->restitution_factor = collider->restitution_factor;
		this->SetMass(collider->mass);
		this->shape_type = collider->shape_type;
	}

	void Collider::Update(){
		PhysicIntent message;
		message.action = PhysicAction::ADD_COLLIDER;
		message.game_object = this->parent;
		MessageBus::Push(message);
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

	Collider* Collider::Clone(){
		return new Collider(this);
	}
}

