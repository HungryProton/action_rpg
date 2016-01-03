#ifndef GAME_CORE_MESSAGING_MESSAGE_DISPATCHER_HPP
#define GAME_CORE_MESSAGING_MESSAGE_DISPATCHER_HPP

#include <vector>

namespace game{

	template<class T>
	class MessageHandler;

	template<class T>
	class MessageDispatcher{
		public:
			void static Push(T);
			void static RegisterHandler(MessageHandler<T>*);
			void static DeregisterHandler(MessageHandler<T>*);

		private:
			static std::vector<MessageHandler<T>*> message_handlers;
	};
}

#include "message_dispatcher.tcc"
#endif //GAME_CORE_MESSAGING_MESSAGE_DISPATCHER_HPP
