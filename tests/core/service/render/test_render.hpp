#ifndef TEST_SERVICE_RENDER_HPP
#define TEST_SERVICE_RENDER_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/service/render/render.hpp"

namespace game{

    const lest::test render[] = {

        CASE("Should open a window"){
            Render* render = new Render();
            EXPECT( render->GetWindow() != nullptr );

            delete render;
        },

    };

    static int run_render_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Render test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( render, argc, argv, std::cout );
    }
}

#endif //TEST_TOOLS_LOGGER_HPP
