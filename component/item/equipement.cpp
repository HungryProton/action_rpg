#include "equipment.hpp"

namespace game{

	Equipment::Equipment(EquipmentType t) : type{t} {
		equiped_item = Entity();
		initialized = false;
	}

	void Equipment::Equip(Entity item){
		equiped_item = item;
		initialized = false;
	}
}
