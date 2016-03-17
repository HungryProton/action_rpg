#include "entity_notifier.hpp"
#include "tools/time.hpp"
#include "tools/random.hpp"
#include "core/messaging/concrete_messages/event_message.hpp"
#include "core/messaging/message_bus.hpp"

namespace game{

	EntityNotifier::EntityNotifier() : Component(){
		this->timer = Time::GetCurrentTime() + Random::NextFloat();
		this->refresh_rate = 1.5f;
	}

	EntityNotifier::EntityNotifier(GameObject* parent){
		if(parent){
			parent->AttachComponent(this);
			parent->RegisterToLocalBus(this);
		}
	}

	EntityNotifier::EntityNotifier(EntityNotifier* en){
		this->notify_speed = en->notify_speed;
		this->notify_position = en->notify_position;
	}

	EntityNotifier* EntityNotifier::Clone(){
		return new EntityNotifier(this);
	}

	void EntityNotifier::Update(){
		if(Time::GetCurrentTime() - this->timer < refresh_rate){ return; }

		if(notify_position){
			EventMessage msg;
			msg.object = this->parent;
			msg.type = EventType::ENTITY_EXISTS;
			MessageBus::Push(msg);
		}
		this->timer = Time::GetCurrentTime();
	}

	void EntityNotifier::OnMessage(EventMessage msg){
		if(msg.type == EventType::DIED){
			if(msg.object == this->parent){
				this->enabled = false;
			}
		}
	}
}
