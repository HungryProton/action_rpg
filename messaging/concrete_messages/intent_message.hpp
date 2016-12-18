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
		DODGE,
		ACTION
	};

	struct IntentMessage : public Message{
		Intent intent;
		glm::vec3 motion_direction;
		glm::vec3 target_direction;

		IntentMessage();
	};
}
#endif //GAME_CORE_MESSAGING_CONCRETE_COMMAND_HPP
