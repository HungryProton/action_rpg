#include "behavior_controller.hpp"
#include "common/uid.hpp"

namespace game{

	BehaviorController::BehaviorController(int priority, bool block){
		action_id_ = Uid::Next();
		priority_ = priority;
		blocking_ = block;
	}

	BehaviorController::~BehaviorController(){ }

	bool BehaviorController::IsBlocked(Entity e){
		Behavior* b = ecs::GetComponent<Behavior>(e);
		return IsBlocked(b);
	}

	bool BehaviorController::IsBlocked(Behavior* b){
		if(b == nullptr){ return false; }
		if(b->current_action_id == -1){ return false; }
		if(b->current_action_id == this->BehaviorController::action_id_){ return false; }
		if(!b->blocking) { return false; }
		if(b->priority > this->BehaviorController::priority_){ return false; }
		return true;
	}

	bool BehaviorController::AcquireLock(Entity e){
		Behavior* b = ecs::GetComponent<Behavior>(e);
		if(b == nullptr){ return true; }
		if(IsBlocked(b)){ return false; }
		b->current_action_id = this->BehaviorController::action_id_;
		b->blocking = this->BehaviorController::blocking_;
		return true;
	}

	void BehaviorController::FreeLock(Entity e){
		Behavior* b = ecs::GetComponent<Behavior>(e);
		if(b == nullptr){ return; }
		b->current_action_id = -1;
	}
}
