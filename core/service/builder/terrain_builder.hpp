#ifndef CORE_SERVICE_TERRAIN_BUILDER_HPP
#define CORE_SERVICE_TERRAIN_BUILDER_HPP

#include "core/service/service.hpp"

namespace game{

    class TerrainBuilder : public Service{
        public: 
            TerrainBuilder();
            ~TerrainBuilder();

            void ClearMemory();

        private:


    };
}
#endif //CORE_SERVICE_TERRAIN_BUILDER_HPP

