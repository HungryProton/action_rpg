#ifndef GAME_CORE_MESSAGING_MESSAGE_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HPP

namespace game{
    
    enum MessageType{
       GENERIC,
    };

    enum MessageSubject{
        UPDATE,
    };

    struct Message{
        MessageType type;
        MessageSubject subject;
        bool children_recursive;
    };
}

#endif //GAME_CORE_MESSAGING_MESSAGE_HPP
