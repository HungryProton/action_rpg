#ifndef GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP

#include <vector>

namespace game{

	template<class T>
	class MessageHandler{
		public:
			MessageHandler();
			virtual ~MessageHandler();
			virtual void NotifyNewMessage(T) final;

		protected:
			std::vector<T> messages_;
	};
}

#include "message_handler.tcc"

#endif //GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
