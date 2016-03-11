#ifndef GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP

#include <vector>

namespace game{

	/*
	 *	Objects that inherits the message handler class must call the UpdateMessages
	 *	function in order to trigger the OnMessage function call
	 *	The message dispatcher will call NotifyMessage(T) to add the message
	 *	in the instance local queue without processing the message.
	 *	UpdateMessage will actually loop through every received message, call the
	 *	OnMessage() function, and clear the queue once it's done.
	 */

	template<class T>
	class MessageHandler{
		public:
			MessageHandler();
			virtual ~MessageHandler();
			virtual void NotifyNewMessage(T) final;

		protected:
			virtual void UpdateMessages() final;
			virtual void OnMessage(T) = 0;

			std::vector<T> messages_;
	};
}

#include "message_handler.tcc"

#endif //GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
