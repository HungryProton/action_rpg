#ifndef GAME_CORE_COMPONENT_BEHAVIOR_CONTROLLER_HPP
#define GAME_CORE_COMPONENT_BEHAVIOR_CONTROLLER_HPP

#include "component.hpp"
#include "behavior.hpp"

namespace game{

	struct BehaviorController : public Component{
			std::map<int, Behavior*> behaviors_;
			void AddAction(Behavior*, int);

			// Component overhead
			BehaviorController();
			BehaviorController(GameObject*);
			BehaviorController(BehaviorController*);
			~BehaviorController();
			virtual BehaviorController* Clone();
			virtual void Notify(SystemEvent);
			virtual void Update();
	};
}

#endif //GAME_CORE_COMPONENT_BEHAVIOR_CONTROLLER_HPP
