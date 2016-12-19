#ifndef GAME_SYSTEM_TRIGGER_DOOR_HPP
#define GAME_SYSTEM_TRIGGER_DOOR_HPP

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "component/trigger/door.hpp"

namespace game{

	class DoorSystem : public System,
										 public MessageHandler<IntentMessage>{
		public:
			DoorSystem();
			~DoorSystem();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void AfterUpdate();
			void OnMessage(IntentMessage);

			void ToggleDoor(Entity, Door*);

			std::vector<IntentMessage> message_list;
	};
}

#endif //GAME_SYSTEM_TRIGGER_DOOR_HPP
