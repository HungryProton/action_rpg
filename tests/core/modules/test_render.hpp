#ifndef TEST_MODULE_RENDER_HPP
#define TEST_MODULE_RENDER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "tools/opengl.hpp"
#include "core/modules/render/render.hpp"

namespace game{

    const lest::test render[] = {
        
        CASE("Should start and stop the rendering module without errors"){
            Render* render_module = new Render();
            render_module->Start();

            EXPECT( !check_gl_error() );
            EXPECT( render_module->GetState() == RUNNING ); 

            render_module->Stop();

            EXPECT( render_module->GetState() == EXITING );
        },

    };

    static int run_render_test_suite(int argc, char** argv){

        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Render test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( render, argc, argv, std::cout );
    }
}

#endif //TEST_MODULE_RENDER_HPP
