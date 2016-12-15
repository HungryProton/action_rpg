#ifndef GAME_SYSTEM_ACTION_DODGE_HPP
#define GAME_SYSTEM_ACTION_DODGE_HPP

#include "system/system.hpp"
#include "system/action/behavior_controller.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	class DodgeSystem : public System,
											public BehaviorController,
											public MessageHandler<IntentMessage>{
		public:
			DodgeSystem();
			~DodgeSystem();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(IntentMessage);
			void UpdateBehaviorComponentFor(Entity);
	};
}

#endif //GAME_SYSTEM_ACTION_DODGE_HPP
