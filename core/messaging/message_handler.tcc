#include "message_bus.hpp"
#include "message_handler.hpp"

namespace ansamb{

	template<class T>
	MessageHandler<T>::MessageHandler(){
		MessageBus::RegisterHandler(this);
	}

	template<class T>
	MessageHandler<T>::~MessageHandler(){
		MessageBus::DeregisterHandler(this);
	}

	template<class T>
	void MessageHandler<T>::Notify(T message){
		this->messages.push_back(message);
	}
}
