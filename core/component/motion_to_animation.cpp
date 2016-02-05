#include "motion_to_animation.hpp"
#include "core/messaging/concrete_messages/animation_command.hpp"
#include "tools/time.hpp"

namespace game{

	MotionToAnimation::MotionToAnimation() : Behavior(){
		this->velocity = nullptr;
		this->previous_velocity = glm::vec3(-1.f, -1.f, -1.f);
	}

	MotionToAnimation::MotionToAnimation(GameObject* parent) : MotionToAnimation(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	MotionToAnimation::MotionToAnimation(MotionToAnimation* m) : MotionToAnimation(){

	}

	MotionToAnimation::~MotionToAnimation(){

	}

	MotionToAnimation* MotionToAnimation::Clone(){
		return new MotionToAnimation(this);
	}

	void MotionToAnimation::NotifyNewComponentAdded(){
		if(this->velocity){ return; }
		this->velocity = &(this->parent->GetComponent<Transform>()->velocity);
	}

	void MotionToAnimation::Update(){
		if(!this->velocity){ return; }

		// Early return if things didn't changed
		if(*(this->velocity) == this->previous_velocity){ return; }

		AnimationCommand message;
		message.action = AnimationAction::PLAY;
		message.direction = Direction::LAST;
		message.loop = true;

		// If the motion stopped
		if(this->velocity->x == 0 && this->velocity->y == 0){
			message.name = "idle";
			this->previous_velocity = *(this->velocity);
			this->parent->BroadcastLocally(message);
			return;
		}

		// Else, get direction
		Direction direction = Direction::LAST;

		if(this->velocity->x == 0){
			this->velocity->y > 0 ? direction = Direction::N : direction = Direction::S;
		} else if(this->velocity->y == 0){
			this->velocity->x > 0 ? direction = Direction::E : direction = Direction::W;
		} else if(this->velocity->x > 0){
			this->velocity->y > 0 ? direction = Direction::NE : direction = Direction::SE;
		} else if(this->velocity->x < 0){
			this->velocity->y > 0 ? direction = Direction::NW : direction = Direction::SW;
		}

		message.direction = direction;

		// Determine whether we should run or walk based on how fast the character
		// moves
		float speed = glm::length(*(this->velocity));
		if(speed > 0.10){
			message.name = "run";
		} else {
			message.name = "walk";
		}

		this->previous_velocity = *(this->velocity);
		this->parent->BroadcastLocally(message);
	}
}
