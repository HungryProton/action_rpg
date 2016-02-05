#include "component.hpp"

namespace game{

	Component::Component(){
		this->is_attached = false;
		this->parent = nullptr;
		this->enabled = true;
		this->manual_update = false;
	}

	Component::~Component(){

	}

	void Component::Update(){

	}

	void Component::NotifyNewComponentAdded(){

	}
}
