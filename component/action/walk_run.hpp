#ifndef GAME_COMPONENT_ACTION_WALK_RUN_HPP_
#define GAME_COMPONENT_ACTION_WALK_RUN_HPP_

namespace game{

	struct WalkRun{
		float walk_speed;
		float run_speed;

		WalkRun();
		WalkRun(float);
		WalkRun(float, float);
	};
}

#endif //GAME_COMPONENT_ACTION_WALK_RUN_HPP_
