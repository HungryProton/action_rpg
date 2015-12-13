#ifndef GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP

#include <vector>

namespace game{

	template<class T>
	class MessageHandler{
		public:
			MessageHandler();
			~MessageHandler();
			void Notify(T);

		protected:
			std::vector<T> messages;
	};
}

#include "message_handler.tcc"

#endif //GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
