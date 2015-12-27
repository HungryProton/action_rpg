#ifndef GAME_CORE_MESSAGE_BUS_HPP
#define GAME_CORE_MESSAGE_BUS_HPP

#include <map>
#include <deque>
#include <vector>

namespace game{

	struct MessageBusHealthReport{
		int registered_handler_count;
		unsigned long received_messages_count;
	};

	template<class T>
	class MessageHandler;

	class MessageBus{
		public:

			template<class T>
			static void Push(T);

			template<class T>
			static void RegisterHandler(MessageHandler<T>*);

			template<class T>
			static void DeregisterHandler(MessageHandler<T>*);

			// For testing purposes only
			static void ResetHealthReport();
			static MessageBusHealthReport GetHealthReport();
		private:
			static MessageBusHealthReport health_report_;
	};
}

#include "message_bus.tcc"

#endif //GAME_CORE_MESSAGE_BUS_HPP
