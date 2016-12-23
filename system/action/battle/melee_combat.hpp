#ifndef GAME_SYSTEM_ACTION_BATTLE_MELEE_COMBAT_HPP
#define GAME_SYSTEM_ACTION_BATTLE_MELEE_COMBAT_HPP

#include "system/system.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "messaging/message_handler.hpp"

namespace game{

	class MeleeCombat : public System,
										  public MessageHandler<IntentMessage>{
		public:
			MeleeCombat();
			~MeleeCombat();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(IntentMessage);
	};
}

#endif //GAME_SYSTEM_ACTION_BATTLE_MELEE_COMBAT_HPP
