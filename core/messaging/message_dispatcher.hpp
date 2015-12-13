#ifndef ANSAMB_CORE_COMMUNICATION_MESSAGE_DISPATCHER_HPP
#define ANSAMB_CORE_COMMUNICATION_MESSAGE_DISPATCHER_HPP

#include <vector>

namespace ansamb{

	template<class T>
	class MessageHandler;

	template<class T>
	class MessageDispatcher{
		public:
			void static Push(T*);
			void static RegisterHandler(MessageHandler<T>*);
			void static DeregisterHandler(MessageHandler<T>*);

		private:
			static std::vector<MessageHandler<T>*> message_handlers;
	};
}

#include "message_dispatcher.tcc"
#endif //ANSAMB_CORE_COMMUNICATION_MESSAGE_DISPATCHER_HPP
