#include "equipment_system.hpp"
#include "component/item/pickup.hpp"
#include "component/item/equipment_slot.hpp"
#include "component/transform.hpp"
#include "component/constraint.hpp"
#include "component/graphic/atlas.hpp"
#include "component/collider.hpp"
#include "ecs/ecs.hpp"
#include <string>

namespace game{

	EquipmentSystem::EquipmentSystem() : System(){
		Require<Transform, EquipmentSlot>();
	}

	EquipmentSystem::~EquipmentSystem(){}

	void EquipmentSystem::BeforeUpdate(){
		this->MessageHandler<EventMessage>::PollMessages();
		this->MessageHandler<ItemCommand>::PollMessages();
	}

	void EquipmentSystem::OnUpdate(Entity e){
		std::vector<EquipmentSlot*> equipment_list = ecs::GetAllComponents<EquipmentSlot>(e);

		for(EquipmentSlot* slot : equipment_list){
			if(slot->initialized){ continue; }
			if(slot->equiped_item.uid == 0){ continue; }

			LOG(DEBUG) << "Initializing " << slot->equiped_item.uid << std::endl;
			Transform* parent_t = ecs::GetComponent<Transform>(e);
			Transform* equipment_t = ecs::GetComponent<Transform>(slot->equiped_item);

			float offset = 0.01 * ((int)slot->type+1);

			equipment_t->position = parent_t->position;
			equipment_t->position.y -= offset;

			Constraint* constraint = ecs::CreateComponent<Constraint>(slot->equiped_item);
			constraint->soft_resolve = false;
			constraint->type = ConstraintType::KEEP_OFFSET;
			constraint->SetOffset(&(equipment_t->position), &(parent_t->position));
			constraint->name = "Equipment " + std::to_string((int)slot->type);

			Atlas* equipment_atlas = ecs::GetComponent<Atlas>(slot->equiped_item);
			Atlas* parent_atlas = ecs::GetComponent<Atlas>(e);
			if(equipment_atlas != nullptr && parent_atlas != nullptr){
				equipment_atlas->SynchronizeWith(parent_atlas);
			}

			slot->initialized = true;
		}
	}

	void EquipmentSystem::OnMessage(ItemCommand cmd){
		switch(cmd.action){
			case ItemAction::PICKUP:

				break;
			case ItemAction::DROP:

				break;
			case ItemAction::USE:
			default:
				break;
		}
	}

	void EquipmentSystem::OnMessage(EventMessage msg){
		if(msg.type != EventType::COLLISION){ return; }
		Entity pickable = msg.from;
		Entity holder = msg.dest;

		// Check if one of the two entity can be picked up;
		PickUp* pickup = ecs::GetComponent<PickUp>(msg.from);
		if(pickup == nullptr){
			pickup = ecs::GetComponent<PickUp>(msg.dest);
			pickable = msg.dest;
			holder = msg.from;
		}
		if(pickup == nullptr){return; } // no entity can be picked, return;

		if(pickup->equiped){ return; } // already equiped, duplicate message, do not process

		std::vector<EquipmentSlot*> slot_list = ecs::GetAllComponents<EquipmentSlot>(holder);
		if(slot_list.empty()){ return; }

		EquipmentSlot* slot = nullptr;
		for(EquipmentSlot* s : slot_list){
			if(s->type == pickup->type){
				slot = s;
			}
		}
		if(slot == nullptr){ return; }
		// Past this point, we detected that a pickable item entered in collision
		// with an entity with equipement

		LOG(DEBUG) << "Equiping " << pickable.uid << " on " << holder.uid << std::endl;

		if(!(pickup->auto_pick)){ return; } // handle that case later

		ecs::RemoveAllComponent<Collider>(pickable);
		ecs::RemoveAllComponent<Texture>(pickable);

		ecs::CreateComponent<Atlas>(pickable)->LoadFromFile(pickup->equiped_atlas);
		pickup->equiped = true;
		slot->Equip(pickable);
	}

	void EquipmentSystem::PickUpItem(){}

	void EquipmentSystem::DropItem(){}

}
