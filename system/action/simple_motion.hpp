#ifndef GAME_SYSTEM_SIMPLE_MOTION_HPP_
#define GAME_SYSTEM_SIMPLE_MOTION_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/intent_message.hpp"

namespace game{

	class SimpleMotionSystem : public System,
														 public MessageHandler<IntentMessage>{
		public:
			SimpleMotionSystem();
			~SimpleMotionSystem();

		protected:
			void BeforeUpdate();
			void OnMessage(IntentMessage);

			std::vector<IntentMessage> intent_buffer_;
	};
}

#endif //GAME_SYSTEM_SIMPLE_MOTION_HPP_
