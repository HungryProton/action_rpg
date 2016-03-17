#include "tools/time.hpp"
#include "melee_attack.hpp"
#include "core/messaging/concrete_messages/animation_command.hpp"
#include "core/messaging/concrete_messages/damages_message.hpp"
#include "core/component/transform.hpp"

namespace game{

	MeleeAttack::MeleeAttack() : Behavior(){
		this->animation_name = "";
		this->damage_modifier = 1;
		this->attacks_durations.clear();
		this->current_attack = 0;
	}

	MeleeAttack::MeleeAttack(GameObject* parent) : MeleeAttack(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	MeleeAttack::MeleeAttack(MeleeAttack* melee_attack) : MeleeAttack(){
		this->animation_name = melee_attack->animation_name;
		this->damage_modifier = melee_attack->damage_modifier;
		this->attacks_durations = melee_attack->attacks_durations;
	}

	MeleeAttack* MeleeAttack::Clone(){
		return new MeleeAttack(this);
	}

	void MeleeAttack::Update(){
		this->MessageHandler<InputMessage>::UpdateMessages();

		if(!this->blocking){ return; }

		float elapsed_time = glfwGetTime() - this->start_time;
		if(elapsed_time >= this->attacks_durations[current_attack]/24.f){
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
		int offset = 0;
		for(int i = 0; i < this->current_attack; i++){
			offset += this->attacks_durations[i];
		}

		animation_message.offset = offset;
		this->parent->BroadcastLocally(animation_message);

		this->blocking = true;
		this->start_time = glfwGetTime();

		this->SendDamageMessage();
		this->current_attack = (this->current_attack + 1)%this->attacks_durations.size();

		// Send sound message

		// Send Damage message Or Attack message?
		// How about stuff that deals damage and aren't attacks?
	}

	void MeleeAttack::SendDamageMessage(){
		DamagesMessage msg;
		msg.type = DamagesType::SLASH;
		msg.amount = this->damage_modifier * 30; // Base weapon damage
		msg.origin = this->parent;
		Area area;
		area.position = this->parent->GetComponent<Transform>()->position;
		area.type = AreaType::CIRCLE;
		area.radius = 1;

		msg.area_of_effect = area;

		MessageBus::Push(msg);
	}
}
