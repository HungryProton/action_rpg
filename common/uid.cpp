#include "uid.hpp"

namespace game{

	long int Uid::Next(){
		return last_++;
	}

	long int Uid::last_ = 0;
}
