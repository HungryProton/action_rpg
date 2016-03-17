#include "health.hpp"
#include "core/messaging/concrete_messages/event_message.hpp"

namespace game{

	Health::Health() : Component(){
		this->amount = 100;
	}

	Health::Health(GameObject* parent) : Health(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Health::Health(Health* health){
		this->amount = health->amount;
	}

	Health* Health::Clone(){
		return new Health(this);
	}

	void Health::Update(){
		this->MessageHandler<DamagesMessage>::UpdateMessages();
	}

	void Health::OnMessage(DamagesMessage msg){
		this->TakeDamages(msg);
	}

	void Health::TakeDamages(DamagesMessage msg){
		// Early return if already dead
		if(this->amount <= 0){ return; }

		if(msg.origin == this->parent){ return; } // Prevent dying from your own attacks
		if(!msg.area_of_effect.IsObjectWithin(this->parent)){ return; }

		this->amount -= msg.amount;
		if(this->amount <= 0){
			EventMessage event;
			event.type = EventType::DIED;
			event.object = this->parent;
			MessageBus::Push(event);
		}
	}
}
