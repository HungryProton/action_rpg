#include "message_bus_stub.hpp"

namespace game{

	int MessageBusStub::GetReceivedMessagesCount(){
		return received_messages_count_;
	}

	int MessageBusStub::GetRegisteredHandlerCount(){
		return registered_handler_count_;
	}

	void MessageBusStub::Reset(){
		received_messages_count_ = 0;
		registered_handler_count_ = 0;
	}

	int MessageBusStub::received_messages_count_ = 0;
	int MessageBusStub::registered_handler_count_ = 0;
}
