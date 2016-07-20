#include "service.hpp"

namespace game{

	void Service::ClearMemory(){
		locator_.ClearMemory();
	}

	Locator Service::locator_;
}
