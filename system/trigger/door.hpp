#ifndef GAME_SYSTEM_TRIGGER_DOOR_HPP
#define GAME_SYSTEM_TRIGGER_DOOR_HPP

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/intent_message.hpp"

namespace game{

	class DoorSystem : public System,
										 public MessageHandler<IntentMessage>{
		public:
			DoorSystem();
			~DoorSystem();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(IntentMessage);
	};
}

#endif //GAME_SYSTEM_TRIGGER_DOOR_HPP
