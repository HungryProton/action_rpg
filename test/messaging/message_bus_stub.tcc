#include "message_bus_stub.hpp"

namespace game{

	template<class T>
	void MessageBusStub::Push(T message){
		MessageBus::Push(message);
		received_messages_count_++;
	}

	template<class T>
	void MessageBusStub::RegisterHandler(MessageHandler<T>* handler){
		MessageBus::RegisterHandler(handler);
		registered_handler_count_++;
	}

	template<class T>
	void MessageBusStub::DeregisterHandler(MessageHandler<T>* handler){
		MessageBus::DeregisterHandler(handler);
		registered_handler_count_--;
	}
}
