#ifndef GAME_CORE_MESSAGING_CONCRETE_COMMAND_HPP
#define GAME_CORE_MESSAGING_CONCRETE_COMMAND_HPP

#include "../message.hpp"
#include "common/glm.hpp"

namespace game{

	enum class Intent{
		RUN,
		WALK,
		IDLE,
		ATTACK,
		BLOCK,
	};

	struct IntentMessage : public Message{
		Intent intent;
		glm::vec3 direction;

		IntentMessage(){ direction = glm::vec3(0.f, 0.f, 0.f); }
	};
}
#endif //GAME_CORE_MESSAGING_CONCRETE_COMMAND_HPP
