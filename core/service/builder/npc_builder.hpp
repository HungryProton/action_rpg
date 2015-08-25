#ifndef CORE_SERVICE_NPC_BUILDER_HPP
#define CORE_SERVICE_NPC_BUILDER_HPP

#include "core/service/service.hpp"

namespace game{

    class NPCBuilder : public Service{
        public: 
            NPCBuilder();
            ~NPCBuilder();

            void ClearMemory();

        private:

    };
}

#endif //CORE_SERVICE_NPC_BUILDER_HPP

