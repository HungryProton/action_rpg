#include "melee_attack.hpp"
#include "core/messaging/concrete_messages/animation_command.hpp"

namespace game{

	MeleeAttack::MeleeAttack() : Component(){
		this->animation_name = "";
		this->damage_modifier = 1;
	}

	MeleeAttack::MeleeAttack(GameObject* parent) : MeleeAttack(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	MeleeAttack::MeleeAttack(MeleeAttack* melee_attack) : MeleeAttack(){
		this->animation_name = melee_attack->animation_name;
		this->damage_modifier = melee_attack->damage_modifier;
	}

	MeleeAttack* MeleeAttack::Clone(){
		return new MeleeAttack(this);
	}

	void MeleeAttack::Update(){
		this->ProcessReceivedMessages();
	}

	void MeleeAttack::ProcessReceivedMessages(){
		for(InputMessage message : this->MessageHandler<InputMessage>::messages_){
			switch(message.command){
				case Command::ATTACK:
					Attack();
					break;
				default:
					break;
			}
		}
		this->MessageHandler<InputMessage>::messages_.clear();
	}

	void MeleeAttack::Attack(){
		AnimationCommand animation_message;
		animation_message.name = this->animation_name;
		animation_message.action = AnimationAction::PLAY;
		this->parent->BroadcastLocally(animation_message);

		// Send sound message

		// Send Damage message Or Attack message?
		// How about stuff that deals damage and aren't attacks?
	}
}
