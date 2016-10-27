#ifndef GAME_SYSTEM_CONTROLLABLE_HPP_
#define GAME_SYSTEM_CONTROLLABLE_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/input_message.hpp"
#include "messaging/concrete_messages/intent_message.hpp"

namespace game{

	// Accumulate all Input messages for a frame, and generate the appropriate
	// intent from the input received
	class Controllable : public System,
											 public MessageHandler<InputMessage>{
		public:
			Controllable();
			~Controllable();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void AfterUpdate();
			void OnMessage(InputMessage);

			IntentMessage intent_;
			bool intent_modified_;
	};
}

#endif //GAME_SYSTEM_CONTROLLABLE_HPP_
