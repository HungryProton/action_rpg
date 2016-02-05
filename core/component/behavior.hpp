#ifndef GAME_CORE_COMPONENT_BEHAVIOR_HPP
#define GAME_CORE_COMPONENT_BEHAVIOR_HPP

#include "component.hpp"

namespace game{

	struct Behavior : public Component{
		bool blocking;
		int group;

		Behavior() : Component(){
			blocking = false;
		}
	};
}

#endif //GAME_CORE_COMPONENT_BEHAVIOR_HPP
