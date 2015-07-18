
#include <iostream>
#include <string>
#include "message.hpp"

namespace game{
    std::string MessageTypeToString(Message msg){
        switch(msg.type){
            case EMPTY:
                return "Empty";
                break;
            case INPUT:
                return "Input";
                break;
            default:
                return "Unknow message type";
        }
    }
}
