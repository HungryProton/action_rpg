#include "equipment_system.hpp"
#include "component/item/pickup.hpp"
#include "component/item/equipment.hpp"
#include "component/transform.hpp"
#include "component/constraint.hpp"
#include "component/atlas.hpp"
#include "ecs/ecs.hpp"
#include <string>

namespace game{

	EquipmentSystem::EquipmentSystem() : System(){
		Require<Transform, Equipment>();
	}

	EquipmentSystem::~EquipmentSystem(){}

	void EquipmentSystem::BeforeUpdate(){
		this->MessageHandler<ItemCommand>::PollMessages();
		this->MessageHandler<EventMessage>::PollMessages();
	}

	void EquipmentSystem::OnUpdate(Entity e){
		std::vector<Equipment*> equipment_list = ecs::GetAllComponents<Equipment>(e);

		for(Equipment* equipment : equipment_list){
			if(equipment->initialized){ continue; }
			if(equipment->equiped_item.uid == 0){ continue; }

			LOG(DEBUG) << "Initializing " << e.uid << std::endl;
			Transform* parent_t = ecs::GetComponent<Transform>(e);
			Transform* equipment_t = ecs::GetComponent<Transform>(equipment->equiped_item);

			float offset = 0.01 * ((int)equipment->type+1);

			equipment_t->position = parent_t->position;
			equipment_t->position.y -= offset;

			Constraint* constraint = ecs::CreateComponent<Constraint>(equipment->equiped_item);
			constraint->soft_resolve = false;
			constraint->type = ConstraintType::KEEP_OFFSET;
			constraint->SetOffset(&(equipment_t->position), &(parent_t->position));
			constraint->name = "Equipment " + std::to_string((int)equipment->type);

			Atlas* equipment_atlas = ecs::GetComponent<Atlas>(equipment->equiped_item);
			Atlas* parent_atlas = ecs::GetComponent<Atlas>(e);
			if(equipment_atlas != nullptr && parent_atlas != nullptr){
				equipment_atlas->SynchronizeWith(parent_atlas);
			}

			equipment->initialized = true;
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
		Entity has_equipment = msg.dest;

		// Check if one of the two entity can be picked up;
		PickUp* pickup = ecs::GetComponent<PickUp>(msg.from);
		if(pickup == nullptr){
			pickup = ecs::GetComponent<PickUp>(msg.dest);
			pickable = msg.dest;
			has_equipment = msg.from;
		}
		if(pickup == nullptr){return; } // no entity can be picked, return;

		Equipment* equipment_component = ecs::GetComponent<Equipment>(has_equipment);
		if(equipment_component == nullptr){ return; }
		// Past this point, we detected that a pickable item entered in collision
		// with an entity with equipement

		if(!(pickup->auto_pick)){ return; } // handle that case later


	}

	void EquipmentSystem::PickUpItem(){}

	void EquipmentSystem::DropItem(){}

}
