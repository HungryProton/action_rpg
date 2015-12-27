#include "input_to_motion.hpp"

namespace game{

	InputToMotion::InputToMotion(){

	}

	InputToMotion::InputToMotion(GameObject* parent) : Component(parent){

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
