#ifndef GAME_SYSTEM_ACTION_FOLLOW_POINTER_HPP
#define GAME_SYSTEM_ACTION_FOLLOW_POINTER_HPP

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/intent_message.hpp"

namespace game{

	class FollowPointer : public System,
												public MessageHandler<IntentMessage>{
		public:
			FollowPointer();
			~FollowPointer();

		protected:
			void OnMessage(IntentMessage);
			void BeforeUpdate();

	};
}

#endif //GAME_SYSTEM_ACTION_FOLLO_POINTER_HPP
