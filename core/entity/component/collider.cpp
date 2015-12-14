#include <cstdlib>
#include <iostream>
#include "../ComponentsList.hpp"
#include "../../GameObject.hpp"

namespace game{

    Collider::Collider() : shape_type(typeid(Collider)){
        this->gravity = 9.81f;
        this->sleeping = false;
        this->SetMass(1.f);
        this->restitution_factor = 0.8f;
    }

    Collider::Collider(GameObject* p) : Collider(){
        p->AttachComponent(this);
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

