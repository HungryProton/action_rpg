#ifndef GAME_CORE_COMPONENT_HPP
#define GAME_CORE_COMPONENT_HPP

#include "core/entity/gameobject/game_object.hpp"

namespace game{

    struct Component{
        bool is_attached;
        bool enabled;

        // ----- Helpers -----
        Component();
        Component(GameObject* p);
        virtual ~Component();
    };
}

#endif // GAME_CORE_COMPONENT_HPP
