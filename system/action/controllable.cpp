#include "controllable.hpp"
#include "component/input/player_controllable.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	Controllable::Controllable() : System(){
		Require<PlayerControllable>();
	}

	Controllable::~Controllable(){}

	void Controllable::BeforeUpdate(){
		this->MessageHandler<InputMessage>::PollMessages();
		GenerateIntentsFromMessages();
	}

	// Take all stored intents, and apply them to every controllable entity
	// Usually we only have a single controllable entity but this system allows
	// simultaneous control of multiple entities
	void Controllable::OnUpdate(Entity entity){
		for(IntentMessage intent : intent_list_){
			intent.from = entity;
			intent.dest = entity;
			MessageBus::Push(intent);
		}
	}

	// Reset intent once they were applied to the entities.
	void Controllable::AfterUpdate(){
		intent_list_.clear();
		message_list_.clear();
	}

	// Store the message upon reception to convert them into intents later
	void Controllable::OnMessage(InputMessage message){
		message_list_.push_back(message);
	}

	void Controllable::GenerateIntentsFromMessages(){
		if(message_list_.empty()){ return; }
		GenerateMotionIntent();
		GenerateDodgeIntent();
		GenerateActionIntent();
		GenerateAttackIntent();
	}

	bool Controllable::HasMotionCommand(InputMessage msg){
		return (msg.command == Command::UP ||
				msg.command == Command::DOWN ||
				msg.command == Command::LEFT ||
				msg.command == Command::RIGHT);
	}

	void Controllable::GenerateMotionIntent(){
		IntentMessage intent;
		bool valid_intent = false;
		int modifier = 0;

		for(InputMessage msg : message_list_){
			msg.status == KeyStatus::JUST_RELEASED ? modifier = 0 : modifier = 1;

			switch(msg.command){
				case Command::UP:
					intent.motion_direction.y = modifier;
					break;
				case Command::DOWN:
					intent.motion_direction.y = -modifier;
					break;
				case Command::LEFT:
					intent.motion_direction.x = -modifier;
					break;
				case Command::RIGHT:
					intent.motion_direction.x = modifier;
					break;
				default:
					break;
			}
			if(HasMotionCommand(msg)){
				valid_intent = true;
				if(msg.first_modifier_pressed){
					intent.intent = Intent::WALK;
				} else {
					intent.intent = Intent::RUN;
				}
			}
		}

		if(valid_intent){
			intent_list_.push_back(intent);
		}
	}

	void Controllable::GenerateDodgeIntent(){
		for(InputMessage msg : message_list_){
			if(msg.command != Command::DODGE){ continue; }
			if(msg.status != KeyStatus::JUST_PRESSED){ continue; }

			IntentMessage intent;
			intent.intent = Intent::DODGE;
			intent.motion_direction = GetDesiredDirectionVector();
			intent_list_.push_back(intent);
			return;
		}
	}

	void Controllable::GenerateActionIntent(){
		for(InputMessage msg : message_list_){
			if(msg.command != Command::ACTION){ continue; }
			if(msg.status != KeyStatus::JUST_PRESSED){ continue; }
			IntentMessage intent;
			intent.intent = Intent::ACTION;
			intent_list_.push_back(intent);
		}
	}

	void Controllable::GenerateAttackIntent(){

	}

	glm::vec3 Controllable::GetDesiredDirectionVector(){
		for(IntentMessage intent : intent_list_){
			if(intent.intent == Intent::RUN || intent.intent == Intent::WALK){
				return intent.motion_direction;
			}
		}
		return glm::vec3(0.f);
	}
}
