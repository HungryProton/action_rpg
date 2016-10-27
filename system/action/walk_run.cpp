#include "walk_run.hpp"
#include "component/action/walk_run.hpp"
#include "component/motion.hpp"
#include "messaging/concrete_messages/animation_command.hpp"

namespace game{

	WalkRunSystem::WalkRunSystem() : System(){
		Require<WalkRun, Motion>();
	}

	WalkRunSystem::~WalkRunSystem(){}

	void WalkRunSystem::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void WalkRunSystem::OnUpdate(Entity){

	}

	void WalkRunSystem::OnMessage(IntentMessage msg){
		if(msg.intent != Intent::WALK && msg.intent != Intent::RUN){ return; }

		Entity e = msg.dest;
		WalkRun* wr = ecs::GetComponent<WalkRun>(e);
		Motion* m = ecs::GetComponent<Motion>(e);
		if(wr == nullptr || m == nullptr){ return; }

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
