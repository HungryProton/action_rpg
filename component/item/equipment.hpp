#ifndef GAME_COMPONENT_ITEMS_EQUIPMENT_HPP_
#define GAME_COMPONENT_ITEMS_EQUIPMENT_HPP_

#include <vector>
#include <string>
#include "ecs/entity/entity.hpp"

namespace game{

	// First value appears behind
	// Last value appears on top
	enum class EquipmentType{BODY, WEAPON, HEAD};

	struct Equipment{
		bool initialized;
		const EquipmentType type;
		Entity equiped_item;

		Equipment(EquipmentType);
		void Equip(Entity);
	};
}

#endif //GAME_COMPONENT_ITEMS_EQUIPMENT_HPP_
