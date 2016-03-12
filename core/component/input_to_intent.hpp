#ifndef GAME_CORE_COMPONENT_INPUT_TO_INTENT_HPP
#define GAME_CORE_COMPONENT_INPUT_TO_INTENT_HPP

#include "component.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"
#include "core/messaging/concrete_messages/intent_message.hpp"
#include "core/messaging/message_handler.hpp"

namespace game{

	struct InputToIntent : public Component,
												 public MessageHandler<InputMessage>{

		InputToIntent();
		InputToIntent(GameObject*);
		InputToIntent(InputToIntent*);
		~InputToIntent();
		virtual InputToIntent* Clone();
		virtual void Update();

		protected:
			virtual void OnMessage(InputMessage);
			void SendIntentIfAny();

			bool input_detected;
			IntentMessage intent;
	};
}
#endif //GAME_CORE_COMPONENT_INPUT_TO_INTENT_HPP
