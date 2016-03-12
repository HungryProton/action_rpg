#ifndef GAME_CORE_COMPONENT_ARTIFICIAL_INTELLIGENCE_RANDOM_HPP
#define GAME_CORE_COMPONENT_ARTIFICIAL_INTELLIGENCE_RANDOM_HPP

#include "../component.hpp"
#include "core/messaging/concrete_messages/intent_message.hpp"

namespace game{

	// Randomly moves in random directions or stay idle for random durations
	struct RandomAi : public Component{
		float timer;
		float action_duration;
		IntentMessage intent;

		RandomAi();
		RandomAi(GameObject*);
		RandomAi(RandomAi*);
		RandomAi* Clone();
		void Update();
	};
}
#endif //GAME_CORE_COMPONENT_ARTIFICIAL_INTELLIGENCE_RANDOM_HPP
