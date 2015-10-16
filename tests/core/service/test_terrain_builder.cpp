#ifndef TEST_SERVICE_TERRAIN_BUILDER_HPP
#define TEST_SERVICE_TERRAIN_BUILDER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/service/builder/helper/terrain_builder.hpp"

namespace game{

    const lest::test terrain_builder[] = {

        CASE("Should generate a map with the proper dimensions"){
            TerrainBuilder* terrain_builder = new TerrainBuilder();

            terrain_builder->SetMapSize(20, 20);
        },
    };

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), terrain_builder);
}

#endif //TEST_SERVICE_INPUT_HPP
