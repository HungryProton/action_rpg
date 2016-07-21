#include "system.hpp"
#include "common/time.hpp"

namespace game{

	System::System(){
		start_time_ = 0;
		last_execution_time_ = 10;
		get_matching_entities_ = nullptr;
	}

	System::~System(){}

	void System::Update(){
		start_time_ = Time::GetCurrentTime();
		BeforeUpdate();
		if(get_matching_entities_ != nullptr){
			for(Entity entity : get_matching_entities_()){
				OnUpdate(entity);
			}
		}
		AfterUpdate();
		last_execution_time_ = Time::GetCurrentTime() - start_time_;
	}

	void System::BeforeUpdate(){}

	void System::OnUpdate(Entity){}

	void System::AfterUpdate(){}

	float System::GetExecutionTime(){
		return this->last_execution_time_;
	}
}
