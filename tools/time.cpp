#include "time.hpp"

namespace game{

	void Time::SetFrameStartTime(double time){
		frame_start_time_ = time;
	}

	float Time::GetDeltaTime(){
		return glfwGetTime() - frame_start_time_;
	}

	float Time::frame_start_time_ = glfwGetTime();
}
