#include "motion.hpp"
#include "tools/time.hpp"

namespace game{

	Motion::Motion() : Motion(nullptr){

	}

	Motion::Motion(GameObject* parent) : System(parent){
		this->type_ = SIMPLE;
		this->direction_ = glm::vec3(0,0,0);
		this->rotation_ = glm::vec3(0,0,0);
		this->scale_ = glm::vec3(0,0,0);
		this->max_force_ = glm::vec3(0,0,0);
	}

	Motion::~Motion(){

	}

	void Motion::RefreshTargetComponentsList(){
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

	void Motion::SetMotionType(MotionType type){
		this->type_ = type;
	}

	MotionType Motion::GetMotionType(){
		return this->type_;
	}

}
