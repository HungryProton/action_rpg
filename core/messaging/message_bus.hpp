#ifndef GAME_CORE_MESSAGE_BUS_HPP
#define GAME_CORE_MESSAGE_BUS_HPP

#include <map>
#include <deque>
#include <vector>

namespace game{

	template<class T>
	class MessageHandler;

	class MessageBus{
		public:

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
			static unsigned int channel_count_;
	};
}

#include "message_bus.tcc"

#endif //GAME_CORE_MESSAGE_BUS_HPP
