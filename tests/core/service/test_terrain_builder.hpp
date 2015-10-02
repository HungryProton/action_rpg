#ifndef TEST_SERVICE_TERRAIN_BUILDER_HPP
#define TEST_SERVICE_TERRAIN_BUILDER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/service/builder/helper/terrain_builder.hpp"

namespace game{

    const lest::test terrain_builder[] = {

        CASE("Should generate a map with the proper dimensions"){
            TerrainBuilder* terrain_builder = new TerrainBuilder();

            terrain_builder->SetMapSize(20, 20);
        },
    };

    static int run_terrain_builder_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Terrain Builder test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run(terrain_builder, argc, argv, std::cout);
    }
}

#endif //TEST_SERVICE_INPUT_HPP
