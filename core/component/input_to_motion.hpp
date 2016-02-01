#ifndef GAME_CORE_COMPONENT_INPUT_TO_MOTION_HPP
#define GAME_CORE_COMPONENT_INPUT_TO_MOTION_HPP

#include "component.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

namespace game{

	struct Motion;

	struct InputToMotion : public Component, public MessageHandler<InputMessage>{
		InputToMotion();
		InputToMotion(GameObject*);
		InputToMotion(InputToMotion*);

		virtual void Update();
		virtual InputToMotion* Clone();
		virtual void NotifyNewComponentAdded();
		void ProcessReceivedMessages();
		void HandleKeyEvent(InputMessage);

		Motion* motion;
	};
}

#endif //GAME_CORE_COMPONENT_INPUT_TO_MOTION_HPP
