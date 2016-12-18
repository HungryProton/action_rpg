#include "behavior.hpp"

namespace game{

	Behavior::Behavior(){
		current_action_id = -1;
		priority = 0;
		blocking = false;
	}
}
