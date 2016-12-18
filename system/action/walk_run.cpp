#include "walk_run.hpp"
#include "component/action/walk_run.hpp"
#include "component/action/behavior.hpp"
#include "component/motion.hpp"
#include "messaging/concrete_messages/animation_command.hpp"
#include "common/uid.hpp"

namespace game{

	WalkRunSystem::WalkRunSystem() : System(), BehaviorController(50){
		Require<WalkRun, Motion>();
	}

	WalkRunSystem::~WalkRunSystem(){}

	void WalkRunSystem::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void WalkRunSystem::OnUpdate(Entity){
		// TODO : Refactor that thing
		// Set a flag in the walkRun component
		// If currently walking / running, update accordingly
		// If blocked, stop updating,
		// but find a way to prevent messagebus spamming with a new
		// walk message every 16 ms
	}

	void WalkRunSystem::OnMessage(IntentMessage msg){
		if(msg.intent != Intent::WALK && msg.intent != Intent::RUN){ return; }

		Entity e = msg.dest;
		WalkRun* wr = ecs::GetComponent<WalkRun>(e);
		Motion* m = ecs::GetComponent<Motion>(e);
		if(wr == nullptr || m == nullptr){ return; }

		if(this->BehaviorController::AcquireLock(e) == false){ return; }

		AnimationCommand cmd;
		cmd.dest = e;
		cmd.action = AnimationAction::PLAY;
		cmd.loop = true;
		cmd.direction = GetDirectionFromVector(glm::vec3(msg.motion_direction.x, -msg.motion_direction.y, msg.motion_direction.z));
		m->direction = msg.motion_direction;

		if(msg.intent == Intent::WALK){
			cmd.name = "walk";
			m->target_speed = wr->walk_speed;
		} else {
			cmd.name = "run";
			m->target_speed = wr->run_speed;
		}

		if(glm::length(msg.motion_direction) == 0){
			cmd.name = "idle";
			cmd.direction = Direction::LAST;
		}
		MessageBus::Push(cmd);
	}
}
