#ifndef CORE_TEST_MESSAGE_BUS_STUB_HPP
#define CORE_TEST_MESSAGE_BUS_STUB_HPP

#include "messaging/message_bus.hpp"

namespace game{

	class MessageBusStub : public MessageBus{
		public:
			static int GetReceivedMessagesCount();
			static int GetRegisteredHandlerCount();
			static void Reset();

			template<class T>
			static void Push(T);

			template<class T>
			static void RegisterHandler(MessageHandler<T>*);

			template<class T>
			static void DeregisterHandler(MessageHandler<T>*);

		private:
			static int received_messages_count_;
			static int registered_handler_count_;
	};
}
#include "message_bus_stub.tcc"
#endif //CORE_TEST_MESSAGE_BUS_STUB_HPP
