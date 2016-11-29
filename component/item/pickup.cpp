#include "pickup.hpp"

namespace game{

	PickUp::PickUp(){
		auto_pick = false;
		type = ItemType::MISC;
	}

	PickUp::PickUp(ItemType _type, bool _auto){
		type = _type;
		auto_pick = _auto;
	}
}
