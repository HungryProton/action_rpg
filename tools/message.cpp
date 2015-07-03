
#include <iostream>
#include <string>
#include "message.hpp"

namespace game{
    std::string MessageSubjectToString(Message msg){
        switch(msg.subject){
            case RENDER:
                return "render";
                break;
            case PHYSIC:
                return "physic";
                break;
            case UPDATE:
                return "update";
                break;
            case PLAYER_INPUT:
                return "playerInput";
                break;
            default:
                return "Unexpected message";
        }
    }
}
