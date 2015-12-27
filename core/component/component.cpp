#include "component.hpp"

namespace game{

	Component::Component(){
		this->is_attached = false;
		this->parent = nullptr;
	}

	Component::~Component(){

	}

	Component::Component(GameObject* parent){
		if(!parent)
			return;
		parent->AttachComponent(this); // This method will define whether the
																	 // component was attached properly
		if(this->is_attached){
			this->parent = parent;
		}
	}

	void Component::Update(){

	}

	void Component::NotifyNewComponentAdded(){

	}
}
