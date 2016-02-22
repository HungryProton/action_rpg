#include "time.hpp"

namespace game{

	void Time::NotifyFrameStart(){
		float current_time = glfwGetTime();
		delta_ = current_time - frame_start_time_;
		frame_start_time_ = current_time;
	}

	float Time::GetDeltaTime(){
		return delta_;
	}

	float Time::GetCurrentDeltaTime(){
		return glfwGetTime() - frame_start_time_;
	}

	float Time::frame_start_time_ = glfwGetTime();
	float Time::delta_ = 0.016f;
}
