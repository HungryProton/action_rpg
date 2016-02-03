#include "message_bus_testing.hpp"

namespace game{

	int MessageBusTesting::GetReceivedMessagesCount(){
		return received_messages_count_;
	}

	int MessageBusTesting::GetRegisteredHandlerCount(){
		return registered_handler_count_;
	}

	void MessageBusTesting::Reset(){
		received_messages_count_ = 0;
		registered_handler_count_ = 0;
	}

	int MessageBusTesting::received_messages_count_ = 0;
	int MessageBusTesting::registered_handler_count_ = 0;
}
