#ifndef GAME_SYSTEM_ACTION_BEHAVIOR_CONTROLLER_HPP
#define GAME_SYSTEM_ACTION_BEHAVIOR_CONTROLLER_HPP

namespace game{

	class BehaviorController{
		public:
			BehaviorController(int, bool block = false);
			~BehaviorController();

		protected:
			long int action_id_;
			int priority_;
			bool blocking_;
	};
}

#endif //GAME_SYSTEM_ACTION_BEHAVIOR_CONTROLLER_HPP
