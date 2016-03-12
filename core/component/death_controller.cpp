#include "death_controller.hpp"
#include "core/messaging/concrete_messages/animation_command.hpp"

namespace game{

	DeathController::DeathController() : Behavior(){
		this->delete_after_death = false;
		this->delay_before_delete = 10;
		this->death_animation = "die";
	}

	DeathController::DeathController(GameObject* parent) : DeathController(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	DeathController::DeathController(DeathController* dc){
		this->delete_after_death = dc->delete_after_death;
		this->delay_before_delete = dc->delay_before_delete;
		this->death_animation = dc->death_animation;
	}

	DeathController* DeathController::Clone(){
		return new DeathController(this);
	}

	void DeathController::Update(){
		this->MessageHandler<EventMessage>::UpdateMessages();
	}

	void DeathController::OnMessage(EventMessage msg){
		if(msg.object != this->parent){ return; }

		AnimationCommand anim_msg;
		anim_msg.name = this->death_animation;
		anim_msg.loop = false;
		anim_msg.action = AnimationAction::PLAY;
		anim_msg.direction = Direction::LAST;

		this->parent->BroadcastLocally(anim_msg);
		this->blocking = true;
	}
}
