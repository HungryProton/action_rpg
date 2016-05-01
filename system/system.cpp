#include "system.hpp"
#include "common/time.hpp"

namespace game{

	System::System(){
		start_time_ = 0;
		last_execution_time_ = 10;
	}

	System::~System(){}

	void System::Update(){
		start_time_ = Time::GetCurrentTime();
		BeforeUpdate();
		for(unsigned long entity : associated_entities_){
			OnUpdate(entity);
		}
		AfterUpdate();
		last_execution_time_ = Time::GetCurrentTime() - start_time_;
	}

	void System::BeforeUpdate(){}

	void System::OnUpdate(unsigned long){}

	void System::AfterUpdate(){}

	void System::AssociateEntity(unsigned long new_id){
		for(unsigned long stored_id : this->associated_entities_){
			if(stored_id == new_id){ return; }
		}
		this->associated_entities_.push_back(new_id);
	}

	void System::DissociateEntity(unsigned long id){
		for(auto it = this->associated_entities_.begin();
				it != this->associated_entities_.end();
				it++){
			if(*it == id){
				this->associated_entities_.erase(it);
				return;
			}
		}
	}

	bool System::IsAssociatedWith(unsigned long id){
		for(unsigned long stored_id : this->associated_entities_){
			if(stored_id == id){
				return true;
			}
		}
		return false;
	}

	float System::GetExecutionTime(){
		return this->last_execution_time_;
	}
}
