#include "controllable.hpp"
#include "component/player_controllable.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	Controllable::Controllable() : System(){
		Require<PlayerControllable>();
	}

	Controllable::~Controllable(){}

	void Controllable::BeforeUpdate(){
		this->MessageHandler<InputMessage>::PollMessages();
	}

	// Take all stored intents, and apply them to every controllable entity
	// Usually we only have a single controllable entity but this system allows
	// simultaneous control of multiple entities
	void Controllable::OnUpdate(Entity entity){
		intent_.dest = entity;
		MessageBus::Push(intent_);
	}

	void Controllable::AfterUpdate(){
		intent_ = IntentMessage();
	}

	// When an input message is received, convert it into an intent and
	// store it. It does not broadcast the intent directly as we need
	// to inject the entities id inside first.
	void Controllable::OnMessage(InputMessage message){
		int modifier = 1;
		if(message.status == KeyStatus::JUST_RELEASED){
			modifier = 0;
		}

		intent_.intent = Intent::RUN;
		if(message.second_modifier_pressed){
			intent_.intent = Intent::WALK;
		}

		switch(message.command){
			case Command::UP:
				intent_.direction.y = +modifier;
				break;

			case Command::DOWN:
				intent_.direction.y = -modifier;
				break;

			case Command::LEFT:
				intent_.direction.x = -modifier;
				break;

			case Command::RIGHT:
				intent_.direction.x = +modifier;
				break;

			case Command::ATTACK:
				intent_.intent = Intent::ATTACK;

			case Command::BLOCK:

			case Command::ACTION:

			case Command::TARGET:

			default:
				break;
		}
	}
}
