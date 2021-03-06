#include <typeindex>
#include "message_dispatcher.hpp"
#include "message_handler.hpp"

namespace game{

	template<class T>
	void MessageDispatcher<T>::Push(T message){
		for(auto message_handler : message_handlers){
			message_handler->NotifyNewMessage(message);
		}
	}

	template<class T>
	void MessageDispatcher<T>::RegisterHandler(MessageHandler<T>* handler){
		// Do not register the handler again if it is already registered
		for(auto registered_handler : message_handlers){
			if(registered_handler == handler){ return; }
		}
		message_handlers.push_back(handler);
	}

	template<class T>
	void MessageDispatcher<T>::DeregisterHandler(MessageHandler<T>* handler){
		for(unsigned int i = 0; i < message_handlers.size(); i++){
			if(message_handlers[i] != handler){ continue; }
			message_handlers.erase(message_handlers.begin() + i);
			return;
		}
	}

	template<class T>
	std::vector<MessageHandler<T>*> MessageDispatcher<T>::message_handlers;
}
