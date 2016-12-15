#ifndef GAME_COMPONENT_ACTION_DODGE_HPP
#define GAME_COMPONENT_ACTION_DODGE_HPP

namespace game{

	struct Dodge{
		float distance;	// in meters
		float duration; // in seconds

		// If it doesn't break too many SOLID rules, maybe put this in
		// protected and friend DodgeSystem class
		bool is_dodging;
		float start_time;

		Dodge();
	};
}

#endif //GAME_COMPONENT_ACTION_DODGE_HPP
