#include "constraint.hpp"
#include "tools/time.hpp"

namespace game{

	Constraint::Constraint() : Component(){
		this->type = ConstraintType::NONE;
		this->value = nullptr;
		this->target_value = nullptr;
		this->soft_resolve = false;
		this->coefficient = 0.5f;
	}

	Constraint::Constraint(GameObject* parent) : Constraint(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Constraint::Constraint(Constraint* constraint){
		this->value = constraint->value;
		this->target_value = constraint->value;
		this->soft_resolve = constraint->soft_resolve;
		this->coefficient = constraint->coefficient;
		this->type = constraint->type;
		this->parent = nullptr;
		this->is_attached = false;
	}

	Constraint* Constraint::Clone(){
		return new Constraint(this);
	}

	void Constraint::Update(){
		switch(this->type){
			case(ConstraintType::COPY):
				SolveCopy();
				break;
			case(ConstraintType::LOWER_THAN):
				SolveLowerThan();
				break;
			case(ConstraintType::GREATER_THAN):
				SolveGreaterThan();
				break;
			case(ConstraintType::NONE):
			default:
				return;
		}
	}

	void Constraint::SolveCopy(){
		if(!soft_resolve){
			*value = *target_value;
			return;
		}

		glm::vec3 diff = *target_value - *value;
		if(dot(diff, diff) <= coefficient*Time::GetDeltaTime()){
			*value = *target_value;
			return;
		}

		*value += diff*coefficient*Time::GetDeltaTime();
	}

	void Constraint::SolveLowerThan(){

	}

	void Constraint::SolveGreaterThan(){

	}
}
