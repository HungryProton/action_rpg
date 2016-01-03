#ifndef GAME_CORE_COMPONENT_INPUT_TO_MOTION_HPP
#define GAME_CORE_COMPONENT_INPUT_TO_MOTION_HPP

#include "component.hpp"

namespace game{

	struct InputToMotion : public Component{
		InputToMotion();
		InputToMotion(GameObject*);
		InputToMotion(InputToMotion*);

		virtual void Update();
		virtual InputToMotion* Clone();
		virtual void NotifyNewComponentAdded();
	};
}

#endif //GAME_CORE_COMPONENT_INPUT_TO_MOTION_HPP
