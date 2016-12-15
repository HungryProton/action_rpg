#include "behavior_controller.hpp"
#include "common/uid.hpp"

namespace game{

	BehaviorController::BehaviorController(int priority, bool block){
		action_id_ = Uid::Next();
		priority_ = priority;
		blocking_ = block;
	}

	BehaviorController::~BehaviorController(){ }
}
