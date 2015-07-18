#ifndef GAME_CORE_SYSTEM_HPP
#define GAME_CORE_SYSTEM_HPP

#include <map>
#include "core/messaging/message.hpp"
#include "core/modules/simulation/gameobject/game_object.hpp"

namespace game{

    struct Component;

    class System{

        public:
            System();
            System(GameObject*);
            virtual ~System();

            virtual void HandleMessage(Message m);
            virtual void UpdateTargetComponents();
            bool IsAttached();
            void Attach();

        protected:
            GameObject* parent;
            bool attached;
    };
}

#endif // GAME_CORE_SYSTEM_HPP
