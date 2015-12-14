#ifndef GAME_CORE_ENTITY_CORE_COMPONENT_HPP
#define GAME_CORE_ENTITY_CORE_COMPONENT_HPP

#include "core/entity/gameobject/game_object.hpp"

namespace game{

    struct Component{
        bool is_attached;
        bool enabled;

        // ----- Helpers -----
        Component();
        Component(GameObject* p);
        virtual ~Component();
        virtual Component* Clone() = 0;
    };
}

#endif // GAME_CORE_ENTITY_CORE_COMPONENT_HPP

