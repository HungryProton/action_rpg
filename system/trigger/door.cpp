#include "door.hpp"
#include "component/trigger/door.hpp"
#include "component/collider.hpp"
#include "component/transform.hpp"
#include "component/graphic/drawable.hpp"

namespace game{

	DoorSystem::DoorSystem() : System(){
		Require<Transform, Collider, Door>();
	}

	DoorSystem::~DoorSystem(){}

	void DoorSystem::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void DoorSystem::OnUpdate(Entity e){
		Transform* door_t = ecs::GetComponent<Transform>(e);
		Door* d = ecs::GetComponent<Door>(e);
		for(IntentMessage msg : message_list){
			Entity emmiter = msg.from;
			Transform* emmiter_t = ecs::GetComponent<Transform>(emmiter);
			if(emmiter_t == nullptr){ continue; }

			float distance = glm::distance(emmiter_t->position, door_t->position);
			if(distance <= d->range){
				ToggleDoor(e, d);
			}
		}
	}

	void DoorSystem::AfterUpdate(){
		message_list.clear();
	}

	void DoorSystem::OnMessage(IntentMessage msg){
		if(msg.intent != Intent::ACTION){ return; }
		message_list.push_back(msg);
	}

	void DoorSystem::ToggleDoor(Entity e, Door* door){
		Collider* c = ecs::GetComponent<Collider>(e);
		Drawable* d = ecs::GetComponent<Drawable>(e);
		if(c == nullptr || d == nullptr || door == nullptr){ return; }

		if(door->is_open){
			c->ghost = false;
			d->invisible = false;
			door->is_open = false;
		} else {
			c->ghost = true;
			d->invisible = true;
			door->is_open = true;
		}
	}
}
