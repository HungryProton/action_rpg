#ifndef GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
#define GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP

#include "../message.hpp"
#include "common/glm.hpp"

namespace game{

	enum class KeyStatus{
		PRESSED,
		JUST_PRESSED,
		RELEASED,
		JUST_RELEASED
	};

	enum class Command{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ATTACK,
		BLOCK,
		DODGE,
		ACTION,
		TARGET,
		RETURN
	};

	struct InputMessage : public Message{
		KeyStatus status;
		Command command;
		bool first_modifier_pressed;
		bool second_modifier_pressed;
		glm::vec2 position; // To be used with TARGET command only
	};
}
#endif //GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
