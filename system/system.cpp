#include "system.hpp"
#include "common/time.hpp"

namespace game{

	System::System(){
		start_time_ = 0;
		last_execution_time_ = 10;
	}

	System::~System(){}

	void System::Update(){
		this->BeforeUpdate();
		start_time_ = Time::GetCurrentTime();
		for(unsigned long entity : associated_entities_){
			OnUpdate(entity);
		}
		last_execution_time_ = Time::GetCurrentTime() - start_time_;
	}

	void System::AssociateEntity(unsigned long new_id){
		for(unsigned long stored_id : this->associated_entities_){
			if(stored_id == new_id){ return; }
		}
		this->associated_entities_.push_back(new_id);
	}

	float System::GetExecutionTime(){
		return this->last_execution_time_;
	}
}
