#include "tools/time.hpp"
#include "melee_attack.hpp"
#include "core/messaging/concrete_messages/animation_command.hpp"

namespace game{

	MeleeAttack::MeleeAttack() : Behavior(){
		this->animation_name = "";
		this->damage_modifier = 1;
		this->attack_duration = 0.5f;
	}

	MeleeAttack::MeleeAttack(GameObject* parent) : MeleeAttack(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	MeleeAttack::MeleeAttack(MeleeAttack* melee_attack) : MeleeAttack(){
		this->animation_name = melee_attack->animation_name;
		this->damage_modifier = melee_attack->damage_modifier;
		this->attack_duration = melee_attack->attack_duration;
	}

	MeleeAttack* MeleeAttack::Clone(){
		return new MeleeAttack(this);
	}

	void MeleeAttack::Update(){
		this->MessageHandler<InputMessage>::UpdateMessages();

		if(!this->blocking){ return; }

		float elapsed_time = glfwGetTime() - this->start_time;
		if(elapsed_time >= this->attack_duration){
			this->blocking = false;
		}
	}

	void MeleeAttack::OnMessage(InputMessage message){
		switch(message.command){
			case Command::ATTACK:
				Attack();
				break;
			default:
				break;
		}
	}

	void MeleeAttack::Attack(){
		if(blocking){ return; }
		AnimationCommand animation_message;
		animation_message.name = this->animation_name;
		animation_message.action = AnimationAction::PLAY;
		this->parent->BroadcastLocally(animation_message);

		this->blocking = true;
		this->start_time = glfwGetTime();

		// Send sound message

		// Send Damage message Or Attack message?
		// How about stuff that deals damage and aren't attacks?
	}
}
