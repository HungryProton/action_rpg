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
	void MessageDispatcher<T>::Push(T message, unsigned int channel){
		if(channel == 0){ return; }
		auto handlers = channels.find(channel);
		if(handlers == channels.end()){ return; }
		for(auto message_handler : handlers->second){
			message_handler->NotifyNewMessage(message);
		}
	}

	template<class T>
	void MessageDispatcher<T>::RegisterHandler(MessageHandler<T>* handler, unsigned int channel){
		if(channel != 0){
			// Check if already registered to the channel
			auto it = channels.find(channel);
			if(it != channels.end()){
				for(auto registered_handler : it->second){
					if(registered_handler == handler){ return; }
				}
				it->second.push_back(handler);
			}
			std::vector<MessageHandler<T>*> handlers;
			handlers.push_back(handler);
			channels.insert(std::make_pair(channel, handlers));
			return;
		}
		// Do not register the handler again if it is already registered
		for(auto registered_handler : message_handlers){
			if(registered_handler == handler){ return; }
		}
		message_handlers.push_back(handler);
	}

	template<class T>
	void MessageDispatcher<T>::DeregisterHandler(MessageHandler<T>* handler, unsigned int channel){
		if(channel != 0){
			auto it = channels.find(channel);
			if(it == channels.end()){ return; }
			for(unsigned int i = 0; i < it->second.size(); i++){
				if(it->second[i] != handler){ continue; }
				it->second.erase(it->second.begin() + i);
			}
		}
		for(unsigned int i = 0; i < message_handlers.size(); i++){
			if(message_handlers[i] != handler){ continue; }
			message_handlers.erase(message_handlers.begin() + i);
			return;
		}
	}

	template<class T>
	std::vector<MessageHandler<T>*> MessageDispatcher<T>::message_handlers;

	template<class T>
	std::map<int, std::vector<MessageHandler<T>*>> MessageDispatcher<T>::channels;
}
