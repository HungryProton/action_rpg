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

		float elapsed_time = Time::GetCurrentTime() - d->start_time;
		if(elapsed_time >= d->duration){
			d->is_dodging = false;
			this->BehaviorController::FreeLock(e);

			AnimationCommand cmd;
			cmd.dest = e;
			cmd.action = AnimationAction::PLAY;
			cmd.loop = true;
			cmd.direction = Direction::LAST;
			cmd.name = "idle";
			MessageBus::Push(cmd);
		}
	}

	void DodgeSystem::OnMessage(IntentMessage msg){
		if(msg.intent != Intent::DODGE){ return; }
		Entity e = msg.dest;
		Dodge* d = ecs::GetComponent<Dodge>(e);
		if(d == nullptr){ return; }
		if(d->is_dodging){ return; } // already dodging, ignore

		if(glm::length(msg.motion_direction) == 0){ return; }
		if(!this->BehaviorController::AcquireLock(e)){ return; }
		d->is_dodging = true;
		d->start_time = Time::GetCurrentTime();

		AnimationCommand cmd;
		cmd.dest = e;
		cmd.action = AnimationAction::PLAY;
		cmd.loop = true;
		cmd.direction = GetDirectionFromVector(glm::vec3(msg.motion_direction.x, -msg.motion_direction.y, msg.motion_direction.z));
		cmd.name = "dodge";

		PhysicIntent intent;
		intent.dest = e;
		intent.action = PhysicAction::APPLY_FORCE;
		intent.force = glm::normalize(msg.motion_direction) * d->distance * 40000.f;

		MessageBus::Push(cmd);
		MessageBus::Push(intent);
	}
}
