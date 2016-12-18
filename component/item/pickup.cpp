#include "pickup.hpp"

namespace game{

	PickUp::PickUp(){
		auto_pick = false;
		equiped = false;
		type = EquipmentType::NONE;
	}

	PickUp::PickUp(EquipmentType _type, bool _auto) : PickUp(){
		type = _type;
		auto_pick = _auto;
	}
}
