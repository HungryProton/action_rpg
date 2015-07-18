#ifndef GAME_CORE_MESSAGE_HPP
#define GAME_CORE_MESSAGE_HPP

#include <string>
//#include <glm/glm.hpp>

namespace game{

    enum MessageType{ EMPTY, INPUT };
    enum MessageSubject{ UPDATE };

    struct Message{
        MessageType type;
        MessageSubject subject; //optionnal

        bool children_recursive = false;
    };

    static std::string MessageTypeToString(Message);
}
#endif // GAME_CORE_MESSAGE_HPP
