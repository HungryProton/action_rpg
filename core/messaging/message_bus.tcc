#include "message_bus.hpp"
#include "message_dispatcher.hpp"
#include "message_handler.hpp"

namespace game{

	template<class T>
	void MessageBus::Push(T message){
		MessageDispatcher<T>::Push(message);
		health_report_.received_messages_count++;
	}

	template<class T>
	void MessageBus::RegisterHandler(MessageHandler<T>* handler){
		MessageDispatcher<T>::RegisterHandler(handler);
		health_report_.registered_handler_count++;
	}

	template<class T>
	void MessageBus::DeregisterHandler(MessageHandler<T>* handler){
		MessageDispatcher<T>::DeregisterHandler(handler);
		health_report_.registered_handler_count--;
	}
}
