#ifndef GAME_SYSTEM_GUI_HPP_
#define GAME_SYSTEM_GUI_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/input_message.hpp"

namespace game{

	class Gui : public System,
							public MessageHandler<InputMessage>{
		public:
			Gui();
			~Gui();

		protected:
			void BeforeUpdate();
			void OnMessage(InputMessage);
	};
}

#endif //GAME_SYSTEM_GUI_HPP_
