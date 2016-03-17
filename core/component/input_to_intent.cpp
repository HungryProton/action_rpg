#include "input_to_intent.hpp"

namespace game{

	InputToIntent::InputToIntent() : Component(){

	}

	InputToIntent::InputToIntent(GameObject* parent) : InputToIntent(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	InputToIntent::InputToIntent(InputToIntent* itoi){

	}

	InputToIntent::~InputToIntent(){

	}

	InputToIntent* InputToIntent::Clone(){
		return new InputToIntent(this);
	}

	void InputToIntent::Update(){
		this->MessageHandler<InputMessage>::UpdateMessages();
		this->SendIntentIfAny();
	}

	void InputToIntent::OnMessage(InputMessage message){
		this->input_detected = true;

		int modifier = 1;
		if(message.status == KeyStatus::JUST_RELEASED){
			modifier = 0;
		}

		if(message.second_modifier_pressed){
			this->intent.intent = Intent::WALK;
		}

		switch(message.command){
			case Command::UP:
				this->intent.direction.y = +modifier;
				break;

			case Command::DOWN:
				this->intent.direction.y = -modifier;
				break;

			case Command::LEFT:
				this->intent.direction.x = -modifier;
				break;

			case Command::RIGHT:
				this->intent.direction.x = +modifier;
				break;

			case Command::ATTACK:

			case Command::BLOCK:

			case Command::ACTION:

			case Command::TARGET:

			default:
				break;
		}
	}

	void InputToIntent::SendIntentIfAny(){
		if(!this->input_detected){ return; }

		if(this->intent.direction == glm::vec3(0.f, 0.f, 0.f)){
			this->intent.intent = Intent::IDLE;
		}
		this->parent->BroadcastLocally(this->intent);
		this->ResetIntent();
		this->input_detected = false;
	}

	void InputToIntent::ResetIntent(){
		this->intent = IntentMessage();
		this->intent.intent = Intent::RUN;
	}
}
