#ifndef GAME_COMPONENT_ACTION_BEHAVIOR_HPP
#define GAME_COMPONENT_ACTION_BEHAVIOR_HPP

namespace game{

	struct Behavior{
		int current_action_id; // if set to -1, it means no actions currently are active
		int priority;
		bool blocking;
	};
}

#endif //GAME_COMPONENT_ACTION_BEHAVIOR_HPP
