#ifndef ANSAMB_CORE_COMMUNICATION_MESSAGE_HANDLER_HPP
#define ANSAMB_CORE_COMMUNICATION_MESSAGE_HANDLER_HPP

#include <vector>

namespace ansamb{

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

#endif //ANSAMB_CORE_COMMUNICATION_MESSAGE_HANDLER_HPP
