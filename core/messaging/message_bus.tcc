#include "message_bus.hpp"
#include "message_dispatcher.hpp"
#include "message_handler.hpp"

namespace game{

	template<class T>
	void MessageBus::Push(T message){
		MessageDispatcher<T>::Push(message);
	}

	template<class T>
	void MessageBus::Push(T message, unsigned int channel){
		MessageDispatcher<T>::Push(message, channel);
	}

	template<class T>
	void MessageBus::RegisterHandler(MessageHandler<T>* handler, unsigned int channel){
		MessageDispatcher<T>::RegisterHandler(handler, channel);
	}

	template<class T>
	void MessageBus::DeregisterHandler(MessageHandler<T>* handler, unsigned int channel){
		MessageDispatcher<T>::DeregisterHandler(handler, channel);
	}
}
