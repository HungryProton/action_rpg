#include "motion.hpp"
#include "tools/time.hpp"
#include "tools/logger.hpp"

namespace game{

	Motion::Motion() : Component(){
		this->type_ = SIMPLE;
		this->direction_ = glm::vec3(0.f,0.f,0.f);
		this->rotation_ = glm::vec3(0.f,0.f,0.f);
		this->scale_ = glm::vec3(0.f,0.f,0.f);
		this->max_force_ = glm::vec3(0.f,0.f,0.f);
		this->transform_ = nullptr;
	}

	Motion::Motion(GameObject* parent) : Motion(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Motion::Motion(Motion* motion){
		this->type_ = motion->type_;
		this->direction_ = motion->direction_;
		this->rotation_ = motion->rotation_;
		this->scale_ = motion->scale_;
		this->max_force_ = motion->max_force_;
		this->transform_ = nullptr;
	}

	Motion::~Motion(){ }

	Motion* Motion::Clone(){
		return new Motion(this);
	}

	void Motion::NotifyNewComponentAdded(){
		this->transform_ = this->parent->GetComponent<Transform>();
	}

	void Motion::Update(){
		switch(this->type_){
			case SIMPLE:
				this->SimpleResolve();
				break;
			case SERVO_CONTROL:
				this->ServoResolve();
				break;
		}
	}

	void Motion::SimpleResolve(){
		float time = Time::GetDeltaTime();
		this->transform_->position += this->direction_* time;
		this->transform_->rotation += this->rotation_ * time;
		this->transform_->scale += this->scale_ * time;
	}

	void Motion::ServoResolve(){

	}
}
