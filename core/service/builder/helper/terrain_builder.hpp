#ifndef CORE_SERVICE_TERRAIN_BUILDER_HPP
#define CORE_SERVICE_TERRAIN_BUILDER_HPP

#include "tools/opengl.hpp"

namespace game{

    class TerrainBuilder{
        public: 
            TerrainBuilder();
            ~TerrainBuilder();

            void ClearMemory();

            void SetMapSize(float, float);
            void SetMaxAltitudeVariation(float);

        private:
            glm::vec2 size_;
            float max_altitude_variation_; 


    };
}
#endif //CORE_SERVICE_TERRAIN_BUILDER_HPP

