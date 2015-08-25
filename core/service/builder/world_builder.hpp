#ifndef GAME_SERVICE_WORLD_BUILDER_HPP
#define GAME_SERVICE_WORLD_BUILDER_HPP

#include <string>
#include "core/service/service.hpp"
#include "core/service/builder/terrain_builder.hpp"
#include "core/service/builder/npc_builder.hpp"

namespace game{

    class WorldBuilder : public Service{
        public:
            WorldBuilder();
            ~WorldBuilder();

            void ClearMemory();

            void GenerateRandomWorld();
            void RebuildWorldFromSave(std::string);

        private:
            void TerrainBuilder* terrain_builder;
            void NPCBuilder* npc_builder;

    };
}

#endif //GAME_SERVICE_WORLD_BUILDER_HPP
