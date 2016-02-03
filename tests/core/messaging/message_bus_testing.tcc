#include "message_bus_testing.hpp"

namespace game{

	template<class T>
	void MessageBusTesting::Push(T message){
		MessageBus::Push(message);
		received_messages_count_++;
	}

	template<class T>
	void MessageBusTesting::Push(T message, unsigned int channel){
		MessageBus::Push(message, channel);
		received_messages_count_++;
	}

	template<class T>
	void MessageBusTesting::RegisterHandler(MessageHandler<T>* handler, unsigned int channel){
		MessageBus::RegisterHandler(handler, channel);
		registered_handler_count_++;
	}

	template<class T>
	void MessageBusTesting::DeregisterHandler(MessageHandler<T>* handler, unsigned int channel){
		MessageBus::DeregisterHandler(handler, channel);
		registered_handler_count_--;
	}
}
