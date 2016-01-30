#include "message_bus.hpp"

namespace game{

	unsigned int MessageBus::RequestNewChannelID(){
		return ++channel_count_;
	}

	unsigned int MessageBus::channel_count_ = 0;
}
