#ifndef GAME_COMPONENT_TRIGGER_DOOR_HPP
#define GAME_COMPONENT_TRIGGER_DOOR_HPP

namespace game{

	struct Door{
		bool locked;

		Door(bool locked = false);
	};
}

#endif //GAME_COMPONENT_TRIGGER_DOOR_HPP
