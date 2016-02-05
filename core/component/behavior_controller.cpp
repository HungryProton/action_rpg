#include "behavior_controller.hpp"

namespace game{

	BehaviorController::BehaviorController() : Component(){
		this->behaviors_.clear();
	}

	BehaviorController::BehaviorController(GameObject* parent) : BehaviorController(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	BehaviorController::BehaviorController(BehaviorController* behavior_controller) : BehaviorController(){
		for(auto c : behavior_controller->behaviors_){
			this->AddAction((Behavior*)c.second->Clone(), c.first);
		}
	}

	BehaviorController::~BehaviorController(){
		for(auto c : this->behaviors_){
			delete c.second;
		}
		this->behaviors_.clear();
	}

	BehaviorController* BehaviorController::Clone(){
		return new BehaviorController(this);
	}

	void BehaviorController::NotifyNewComponentAdded(){
		for(auto behavior : this->behaviors_){
			behavior.second->NotifyNewComponentAdded();
		}
	}

	void BehaviorController::AddAction(Behavior* action, int priority){
		// Prevent messing up the updating order
		action->manual_update = true;

		// Add the behavior to the controller
		this->behaviors_.insert(std::make_pair(priority, action));
	}

	void BehaviorController::Update(){
		for(auto behavior : this->behaviors_){
			behavior.second->Update();
			//if(behavior.second->blocking){
			//	break;
			//}
		}
	}
}
