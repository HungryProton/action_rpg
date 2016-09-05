#ifndef GAME_SYSTEM_WALK_RUN_HPP_
#define GAME_SYSTEM_WALK_RUN_HPP_
// Temporary name

#include "system/system.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	class WalkRunSystem : public System,
												public MessageHandler<IntentMessage>{
		public:
			WalkRunSystem();
			~WalkRunSystem();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(IntentMessage);
	};
}

#endif //GAME_SYSTEM_WALK_RUN_HPP_
