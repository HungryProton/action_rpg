#include "pickup.hpp"

namespace game{

	PickUp::PickUp(){
		auto_pick = false;
		type = EquipmentType::NONE;
	}

	PickUp::PickUp(EquipmentType _type, bool _auto){
		type = _type;
		auto_pick = _auto;
	}
}
