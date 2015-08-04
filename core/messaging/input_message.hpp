#ifndef GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
#define GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP

#include "message.hpp"

namespace game{

    enum KeyStatus{
        KEY_PRESSED,
        KEY_RELEASED
    };

    struct InputMessage : public Message{
        KeyStatus status;
    };
}
#endif //GAME_CORE_MESSAGING_INPUT_MESSAGE_HPP
