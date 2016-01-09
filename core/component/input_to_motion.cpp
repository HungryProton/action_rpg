#include "input_to_motion.hpp"

namespace game{

	InputToMotion::InputToMotion() : Component(){

	}

	InputToMotion::InputToMotion(GameObject* parent) : InputToMotion(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	InputToMotion::InputToMotion(InputToMotion* input_to_motion){

	}

	InputToMotion* InputToMotion::Clone(){
		return new InputToMotion(this);
	}

	void InputToMotion::Update(){

	}

	void InputToMotion::NotifyNewComponentAdded(){

	}
}
