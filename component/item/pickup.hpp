#ifndef GAME_COMPONENT_PICKUP_HPP_
#define GAME_COMPONENT_PICKUP_HPP_

namespace game{

	enum class ItemType{HEAD, BODY, MELEE, RANGED, BONUS, MISC};

	struct PickUp{
		ItemType type;
		bool auto_pick; // if false, user have to press a key to pick the item
										// if true, item will be automatically picked on contact
		PickUp();
		PickUp(ItemType, bool);
	};
}

#endif //GAME_COMPONENT_PICKUP_HPP_
