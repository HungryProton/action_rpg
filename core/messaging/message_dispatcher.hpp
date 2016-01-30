#ifndef GAME_CORE_MESSAGING_MESSAGE_DISPATCHER_HPP
#define GAME_CORE_MESSAGING_MESSAGE_DISPATCHER_HPP

#include <vector>
#include <map>

namespace game{

	template<class T>
	class MessageHandler;

	template<class T>
	class MessageDispatcher{
		public:
			void static Push(T);
			void static Push(T, unsigned int);
			void static RegisterHandler(MessageHandler<T>*, unsigned int channel = 0);
			void static DeregisterHandler(MessageHandler<T>*, unsigned int channel = 0);

		private:
			static std::vector<MessageHandler<T>*> message_handlers;
			static std::map<int, std::vector<MessageHandler<T>*>> channels;
	};
}

#include "message_dispatcher.tcc"
#endif //GAME_CORE_MESSAGING_MESSAGE_DISPATCHER_HPP
