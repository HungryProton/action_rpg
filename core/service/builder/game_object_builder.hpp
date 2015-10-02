#ifndef CORE_SERVICE_GAME_OBJECT_BUILDER_HPP
#define CORE_SERVICE_GAME_OBJECT_BUILDER_HPP

#include <vector>
#include "core/entity/gameobject/game_object.hpp"
#include "core/service/service.hpp"

namespace game{

    class GameObjectBuilder : public Service{
        public:
            GameObjectBuilder();
            ~GameObjectBuilder();

            void ClearMemory();
            GameObject* CreateBlank();

        private:
            std::vector<GameObject*> game_object_list_;
    };
}

#endif //CORE_SERVICE_GAME_OBJECT_BUILDER_HPP
