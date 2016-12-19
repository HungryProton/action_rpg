#ifndef GAME_COMPONENT_TRIGGER_DOOR_HPP
#define GAME_COMPONENT_TRIGGER_DOOR_HPP

namespace game{

	struct Door{
		bool locked;
		bool is_open;
		float range; // maximum distance from the door (in m) to be opened

		Door(bool is_open = false, bool locked = false);
	};
}

#endif //GAME_COMPONENT_TRIGGER_DOOR_HPP
