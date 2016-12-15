#include "dodge.hpp"
#include "component/action/dodge.hpp"
#include "component/action/behavior.hpp"
#include "component/transform.hpp"
#include "common/logger.hpp"
#include "common/time.hpp"
#include "messaging/concrete_messages/animation_command.hpp"
#include "messaging/concrete_messages/physic_intent.hpp"

namespace game{

	DodgeSystem::DodgeSystem() : System(), BehaviorController(20, true){
		Require<Transform, Dodge>();
	}

	DodgeSystem::~DodgeSystem(){}

	void DodgeSystem::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void DodgeSystem::OnUpdate(Entity e){
		Dodge* d = ecs::GetComponent<Dodge>(e);
		if(!d->is_dodging){ return; }

		float remaining_time = Time::GetCurrentTime() - d->start_time;
		if(remaining_time <= 0){
			d->is_dodging = false;
			Behavior* b = ecs::GetComponent<Behavior>(e);
			if(b == nullptr){ return; }
			b->current_action_id = -1;
		}
	}

	void DodgeSystem::OnMessage(IntentMessage msg){
		if(msg.intent != Intent::DODGE){ return; }
		Entity e = msg.dest;
		Dodge* d = ecs::GetComponent<Dodge>(e);
		if(d == nullptr){ return; }

		UpdateBehaviorComponentFor(e);

		AnimationCommand cmd;
		cmd.dest = e;
		cmd.action = AnimationAction::PLAY;
		cmd.loop = true;
		cmd.direction = GetDirectionFromVector(glm::vec3(msg.motion_direction.x, -msg.motion_direction.y, msg.motion_direction.z));
		cmd.name = "dodge";

		PhysicIntent intent;
		intent.action = PhysicAction::APPLY_FORCE;
		intent.force = msg.motion_direction * d->distance;

		MessageBus::Push(cmd);
		MessageBus::Push(intent);
	}

	void DodgeSystem::UpdateBehaviorComponentFor(Entity e){
		Behavior* b = ecs::GetComponent<Behavior>(e);
		if(b == nullptr){ return; }
		if(b->current_action_id >= 0){
			if(b->priority < this->BehaviorController::priority_){ return; }
			if(b->current_action_id == this->BehaviorController::action_id_){ return; }
		}

		b->current_action_id = this->BehaviorController::action_id_;
		b->priority = this->BehaviorController::priority_;
		b->blocking = true;
	}
}
