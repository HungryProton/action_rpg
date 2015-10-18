#include <iostream>
#include <cstdlib>
#include <typeindex>
#include <typeinfo>
#include "system.hpp"
#include "core/entity/gameobject/game_object.hpp"

namespace game{

    System::System(){
        this->attached = false;
    }

    System::System(GameObject* p) : System(){
        this->parent = p;
        p->AttachSystem(this);
    }

    System::~System(){

    }

    void System::HandleMessage(Message message){

    }

    void System::UpdateTargetComponents(){

    }

		void System::Update(){

		}

    bool System::IsAttached(){
        return this->attached;
    }

    void System::Attach(){
        this->attached = true;
    }
}
