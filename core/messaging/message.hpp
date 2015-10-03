#ifndef GAME_CORE_MESSAGING_MESSAGE_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HPP

#include <iostream>
#include <typeindex>
#include "message_handler.hpp"
#include "tools/logger.hpp"

namespace game{

    enum MessageType{
       GENERIC,
       INPUT,
    };

    enum MessageSubject{
        EMPTY,
        UPDATE,
    };

    struct Message{
        MessageType type;
        MessageSubject subject;
        bool children_recursive;

        virtual void Dispatch(IMessageHandler* message_handler){
            LOG(INFO) << "type id : " << typeid(*this).name() << std::endl;
            message_handler->On(*this);
        }
    };
}

#endif //GAME_CORE_MESSAGING_MESSAGE_HPP
