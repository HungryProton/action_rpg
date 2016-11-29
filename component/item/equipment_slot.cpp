#include "equipment_slot.hpp"

namespace game{

	EquipmentSlot::EquipmentSlot(EquipmentType t) : type{t} {
		equiped_item = Entity();
		initialized = false;
	}

	void EquipmentSlot::Equip(Entity item){
		equiped_item = item;
		initialized = false;
	}
}
