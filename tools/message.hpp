#ifndef GAME_CORE_MESSAGE_HPP
#define GAME_CORE_MESSAGE_HPP

#include <string>
//#include <glm/glm.hpp>

namespace game{

    enum Subject{ EMPTY, RENDER, PHYSIC, UPDATE, PLAYER_INPUT, MOVE };
    enum Body{ PHYSIC_IMPULSE, PHYSIC_PROCESS, 
               INPUT_RIGHT, INPUT_LEFT,
               LEFT, RIGHT };

    struct Message{
        Subject subject;
        Body body;

        float numeric_value;
 //       glm::vec3 vec;
        bool children_recursive = false;
    };

    std::string MessageSubjectToString(Message);
}
#endif // GAME_CORE_MESSAGE_HPP
