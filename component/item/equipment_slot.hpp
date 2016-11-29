#ifndef GAME_COMPONENT_ITEMS_EQUIPMENT_SLOT_HPP_
#define GAME_COMPONENT_ITEMS_EQUIPMENT_SLOT_HPP_

#include <vector>
#include <string>
#include "ecs/entity/entity.hpp"

namespace game{

	// First value appears behind
	// Last value appears on top
	enum class EquipmentType{BODY, WEAPON, HEAD};

	struct EquipmentSlot{
		bool initialized;
		const EquipmentType type;
		Entity equiped_item;

		EquipmentSlot(EquipmentType);
		void Equip(Entity);
	};
}

#endif //GAME_COMPONENT_ITEMS_EQUIPMENT_SLOT_HPP_
