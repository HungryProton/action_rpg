#include "system.hpp"
#include "common/time.hpp"

namespace game{

	System::System(){
		start_time_ = 0;
		last_execution_time_ = 10;
		get_matching_entities_ = nullptr;
		target_frame_duration_ = -1;	 // if -1, update as fast as possible
	}

	System::System(float time) : System(){
		target_frame_duration_ = time;
	}

	System::~System(){}

	void System::Update(){
		if(!IsReadyToUpdate()){ return; }
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

	bool System::IsReadyToUpdate(){
		if(target_frame_duration_ == -1){ return true; }
		float dt = Time::GetCurrentTime() - start_time_;
		return dt >= target_frame_duration_;
	}

	void System::SetDesiredFrameDuration(float time){
		target_frame_duration_ = time;
	}
}
