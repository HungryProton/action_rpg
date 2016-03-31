#ifndef GAME_CORE_COMPONENT_INTENT_TO_MOTION_HPP
#define GAME_CORE_COMPONENT_INTENT_TO_MOTION_HPP

#include "behavior.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/messaging/concrete_messages/intent_message.hpp"

namespace game{

	struct Motion;

	struct IntentToMotion : public Behavior,
													public MessageHandler<IntentMessage>{
		IntentToMotion();
		IntentToMotion(GameObject*);
		IntentToMotion(IntentToMotion*);

		virtual void Update();
		virtual IntentToMotion* Clone();
		virtual void Notify(SystemEvent);

		Motion* motion;
		float run_speed;
		float walk_speed;

		private:
			virtual void OnMessage(IntentMessage);
	};
}

#endif //GAME_CORE_COMPONENT_INTENT_TO_MOTION_HPP
