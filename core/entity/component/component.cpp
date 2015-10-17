#include "component.hpp"

namespace game{

    Component::Component(){
        this->is_attached = false;
    }

    Component::~Component(){

    }

    Component::Component(GameObject* parent){
			if(!parent)
				return;
			parent->AttachComponent(this); // This method will define whether the
																		 // component was attached properly
  	}
}
