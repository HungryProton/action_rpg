#include "door.hpp"

namespace game{

	Door::Door(bool o, bool l){
		locked = l;
		is_open = o;
		range = 1.5;
	}
}
