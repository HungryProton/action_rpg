#ifndef GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
#define GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP

#include "../message.hpp"

namespace game{

    enum KeyStatus{
        KEY_PRESSED,
        KEY_RELEASED,
				KEY_JUST_RELEASED
    };

    enum class Command{
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
				ATTACK,
        ACTIVATE,
    };

    struct InputMessage : public Message{
        KeyStatus status;
        Command command;
				bool modifier_pressed;
    };
}
#endif //GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
