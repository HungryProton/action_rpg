#ifndef TEST_SERVICE_IMAGE_HELPER_HPP
#define TEST_SERVICE_IMAGE_HELPER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/service/helper/image_helper.hpp"

namespace game{

    const lest::test image_helper[] = {

        CASE("Should create a GL_texture ID upon new texture request"){
            ImageHelper helper;
            Image *img = helper.LoadFromFile("tests/resources/1.png");

            EXPECT( img != nullptr );
            EXPECT( img->GL_texture != 0 );

            helper.ClearMemory();
        },

    };

    static int run_image_helper_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Image Helper test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( image_helper, argc, argv, std::cout );
    }
}

#endif //TEST_SERVICE_INPUT_HPP
