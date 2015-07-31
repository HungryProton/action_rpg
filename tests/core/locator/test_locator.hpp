#ifndef TEST_SERVICE_RENDER_HPP
#define TEST_SERVICE_RENDER_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/service/render/render.hpp"

namespace game{

    const lest::test locator[] = {

        CASE("Should return the correct service after calling provide"){
            // Create a service
            Render* render = new Render();

            //Register the service to the locator
            Locator::Provide(render);

            // Try to get the service from the locator
            Render* render_from_locator = Locator::Get<Render>();

            // Both should be identical
            EXPECT( render_from_locator == render );

            // Clear memory
            delete render;
        },
    };

    static int run_locator_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Locator test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( locator, argc, argv, std::cout );
    }
}

#endif //TEST_TOOLS_LOGGER_HPP
