#include "tools/logger.hpp"
#include "message_bus.hpp"
#include "message_handler.hpp"

namespace game{

	template<class T>
	MessageHandler<T>::MessageHandler(){
		MessageBus::RegisterHandler(this);
	}

	template<class T>
	MessageHandler<T>::~MessageHandler(){
		MessageBus::DeregisterHandler(this);
	}

	template<class T>
	void MessageHandler<T>::NotifyNewMessage(T message){
		this->messages_.push_back(message);
	}
}
