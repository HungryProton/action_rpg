#ifndef GAME_CORE_ENTITY_CORE_COMPONENT_HPP
#define GAME_CORE_ENTITY_CORE_COMPONENT_HPP

namespace game{

	struct Component{
		virtual Component* Clone() = 0;
		unsigned long parent;
	};
}

#endif // GAME_CORE_ENTITY_CORE_COMPONENT_HPP

