#include "input_to_motion.hpp"
#include "motion.hpp"

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
		ProcessReceivedMessages();
	}

	void InputToMotion::NotifyNewComponentAdded(){
		if(!this->parent){ return; }
		this->motion_ = this->parent->GetComponent<Motion>();
	}

	void InputToMotion::ProcessReceivedMessages(){
		for(auto message : this->MessageHandler<InputMessage>::messages_){
			this->HandleKeyEvent(message);
		}
	}

	void InputToMotion::HandleKeyEvent(InputMessage message){
		int modifier;
		message.status == KEY_PRESSED ? modifier = 1 : modifier = 0;

		switch(message.command){
			case(Command::MOVE_UP):
				motion_->direction_.y = modifier;
				break;
			case(Command::MOVE_DOWN):
				motion_->direction_.y = -modifier;
				break;
			case(Command::MOVE_LEFT):
				motion_->direction_.x = -modifier;
				break;
			case(Command::MOVE_RIGHT):
				motion_->direction_.x = modifier;
				break;
			default:
				return;
		}
	}
}
