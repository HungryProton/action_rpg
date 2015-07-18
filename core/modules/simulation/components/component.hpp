#ifndef GAME_CORE_COMPONENT_HPP
#define GAME_CORE_COMPONENT_HPP

#include <typeindex>
#include "core/modules/simulation/gameobject/game_object.hpp"

namespace game{

    struct Component{
        bool is_attached;
        bool enabled;

        // ----- Helpers -----
        Component(){ this->is_attached = false; }
        Component(GameObject* p) : Component(){ p->AttachComponent(this); }
        virtual ~Component(){} ;
    };
}

#endif // GAME_CORE_COMPONENT_HPP
