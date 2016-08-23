#ifndef GAME_SYSTEM_CONTROLLABLE_HPP_
#define GAME_SYSTEM_CONTROLLABLE_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/input_message.hpp"

namespace game{

	class Controllable : public System,
											 public MessageHandler<InputMessage>{
		public:
			Controllable();
			~Controllable();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(InputMessage);
	};
}

#endif //GAME_SYSTEM_CONTROLLABLE_HPP_
