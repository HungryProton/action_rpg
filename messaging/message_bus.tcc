#include "message_bus.hpp"
#include "message_dispatcher.hpp"
#include "message_handler.hpp"

namespace game{

	template<class T>
	void MessageBus::Push(T message){
		MessageDispatcher<T>::Push(message);
	}

	template<class T>
	void MessageBus::RegisterHandler(MessageHandler<T>* handler){
		MessageDispatcher<T>::RegisterHandler(handler);
	}

	template<class T>
	void MessageBus::DeregisterHandler(MessageHandler<T>* handler){
		MessageDispatcher<T>::DeregisterHandler(handler);
	}
}
