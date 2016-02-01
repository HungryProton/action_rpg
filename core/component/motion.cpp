#include "motion.hpp"
#include "tools/time.hpp"
#include "tools/logger.hpp"

namespace game{

	Motion::Motion() : Component(){
		this->type = SIMPLE;
		this->direction = glm::vec3(0.f,0.f,0.f);
		this->rotation = glm::vec3(0.f,0.f,0.f);
		this->scale = glm::vec3(0.f,0.f,0.f);
		this->max_force = glm::vec3(0.f,0.f,0.f);
		this->target_speed = 0;
		this->transform = nullptr;
	}

	Motion::Motion(GameObject* parent) : Motion(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Motion::Motion(Motion* motion) : Motion(){
		this->type = motion->type;
		this->direction = motion->direction;
		this->rotation = motion->rotation;
		this->scale = motion->scale;
		this->max_force = motion->max_force;
		this->target_speed = motion->target_speed;
		this->transform = nullptr;
	}

	Motion::~Motion(){ }

	Motion* Motion::Clone(){
		return new Motion(this);
	}

	void Motion::NotifyNewComponentAdded(){
		if(!this->parent){ return; }
		this->transform = this->parent->GetComponent<Transform>();
	}

	void Motion::Update(){
		switch(this->type){
			case SIMPLE:
				this->SimpleResolve();
				break;
			case SERVO_CONTROL:
				this->ServoResolve();
				break;
		}
	}

	void Motion::SimpleResolve(){
		if(!this->transform){ return; }
		float time = Time::GetDeltaTime();
		if(glm::length(this->direction) != 0){
			this->transform->position += glm::normalize(this->direction) * this->target_speed * time;
		}
		this->transform->rotation += this->rotation * time;
		this->transform->scale += this->scale * time;
	}

	void Motion::ServoResolve(){

	}
}
