#ifndef GAME_COMPONENT_PICKUP_HPP_
#define GAME_COMPONENT_PICKUP_HPP_

#include "component/common.hpp"

namespace game{

	struct PickUp{
		EquipmentType type;
		bool auto_pick; // if false, user have to press a key to pick the item
										// if true, item will be automatically picked on contact
		std::string exposition_texture; // Texture used when item is on ground
		std::string equiped_atlas;	// Texture used when item is equiped

		PickUp();
		PickUp(EquipmentType, bool);
	};
}

#endif //GAME_COMPONENT_PICKUP_HPP_
