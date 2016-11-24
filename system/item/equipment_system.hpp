#ifndef GAME_SYSTEM_ITEM_EQUIPMENT_HPP_
#define GAME_SYSTEM_ITEM_EQUIPMENT_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/item_command.hpp"
#include "messaging/concrete_messages/event_message.hpp"

namespace game{

	class EquipmentSystem : public System,
													public MessageHandler<ItemCommand>,
													public MessageHandler<EventMessage>{
		public:
			EquipmentSystem();
			~EquipmentSystem();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity e);
			void OnMessage(ItemCommand);
			void OnMessage(EventMessage);

			void PickUpItem();
			void DropItem();
	};
}

#endif //GAME_SYSTEM_ITEM_EQUIPMENT_HPP_
