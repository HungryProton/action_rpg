#include "terrain_builder.hpp"

namespace game{

    TerrainBuilder::TerrainBuilder(){

    }

    TerrainBuilder::~TerrainBuilder(){

    }

    void TerrainBuilder::ClearMemory(){

    }

    void TerrainBuilder::SetMapSize(float width, float height){
        this->size_.x = width;
        this->size_.y = height;
    }

    void TerrainBuilder::SetMaxAltitudeVariation(float variation){
        this->max_altitude_variation_ = variation;
    }
}
