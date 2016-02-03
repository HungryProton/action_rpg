#ifndef CORE_TEST_MESSAGE_BUS_HPP
#define CORE_TEST_MESSAGE_BUS_HPP

#include "core/messaging/message_bus.hpp"

namespace game{

	class MessageBusTesting : public MessageBus{
		public:
			static int GetReceivedMessagesCount();
			static int GetRegisteredHandlerCount();
			static void Reset();

			template<class T>
			static void Push(T);

			template<class T>
			static void Push(T, unsigned int);

			template<class T>
			static void RegisterHandler(MessageHandler<T>*, unsigned int channel = 0);

			template<class T>
			static void DeregisterHandler(MessageHandler<T>*, unsigned int channel = 0);

			static unsigned int RequestNewChannelID();

		private:
			static int received_messages_count_;
			static int registered_handler_count_;
	};
}

#endif //CORE_TEST_MESSAGE_BUS_HPP
