#ifndef GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
#define GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP

#include "message.hpp"

namespace game{

    enum KeyStatus{
        KEY_PRESSED,
        KEY_RELEASED
    };

    enum Command{
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        ACTIVATE,
    };

    struct InputMessage : public Message{
        KeyStatus status;
        Command command;
    };
}
#endif //GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
