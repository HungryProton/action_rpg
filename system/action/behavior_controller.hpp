#ifndef GAME_SYSTEM_ACTION_BEHAVIOR_CONTROLLER_HPP
#define GAME_SYSTEM_ACTION_BEHAVIOR_CONTROLLER_HPP

#include "ecs/ecs.hpp"
#include "component/action/behavior.hpp"

namespace game{

	class BehaviorController{
		public:
			BehaviorController(int, bool block = true);
			~BehaviorController();

		protected:
			bool AcquireLock(Entity);
			void FreeLock(Entity);
			bool IsBlocked(Entity);
			bool IsBlocked(Behavior*);

			long int action_id_;
			int priority_;
			bool blocking_;
	};
}

#endif //GAME_SYSTEM_ACTION_BEHAVIOR_CONTROLLER_HPP
