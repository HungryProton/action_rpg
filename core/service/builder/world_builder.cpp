#include "core/locator/locator.hpp"
#include "core/game/game.hpp"
#include "world_builder.hpp"

namespace game{

    WorldBuilder::WorldBuilder(){
        this->terrain_builder_ = new TerrainBuilder();
        this->npc_builder_ = new NPCBuilder();
    }

    WorldBuilder::~WorldBuilder(){
        this->ClearMemory();
    }

    void WorldBuilder::ClearMemory(){
        this->npc_builder_->ClearMemory();
        this->terrain_builder_->ClearMemory();

        delete this->npc_builder_;
        delete this->terrain_builder_;
    }

    void WorldBuilder::RebuildWorldFromSave( std::string save_file_path ){

    }

    void WorldBuilder::GenerateRandomWorld(){

    }
}


