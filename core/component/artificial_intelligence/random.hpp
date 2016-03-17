#ifndef GAME_CORE_COMPONENT_ARTIFICIAL_INTELLIGENCE_RANDOM_HPP
#define GAME_CORE_COMPONENT_ARTIFICIAL_INTELLIGENCE_RANDOM_HPP

#include "../component.hpp"
#include "core/messaging/concrete_messages/intent_message.hpp"
#include "core/messaging/concrete_messages/event_message.hpp"
#include "core/messaging/message_handler.hpp"

namespace game{

	// Randomly moves in random directions or stay idle for random durations
	struct RandomAi : public Component,
										public MessageHandler<EventMessage>{
		float timer;
		float action_duration;
		IntentMessage intent;

		RandomAi();
		RandomAi(GameObject*);
		RandomAi(RandomAi*);
		RandomAi* Clone();
		void Update();

		private:
			void AttackIfNearbyEntity();
			void OnMessage(EventMessage);
			std::vector<GameObject*> nearby_entities;
			void ClearNearbyEntities();
	};
}
#endif //GAME_CORE_COMPONENT_ARTIFICIAL_INTELLIGENCE_RANDOM_HPP
