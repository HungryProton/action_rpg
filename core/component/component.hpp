#ifndef GAME_CORE_ENTITY_CORE_COMPONENT_HPP
#define GAME_CORE_ENTITY_CORE_COMPONENT_HPP

#include "core/entity/game_object.hpp"

namespace game{

	struct Component{
		bool is_attached;
		bool enabled;
		GameObject* parent;

		// ----- Helpers -----
		Component();
		Component(GameObject* p);
		virtual ~Component();
		virtual Component* Clone() = 0;
		virtual void Update();
		virtual void NotifyNewComponentAdded();
	};
}

#endif // GAME_CORE_ENTITY_CORE_COMPONENT_HPP

