#ifndef TEST_SERVICE_IMAGE_HELPER_HPP
#define TEST_SERVICE_IMAGE_HELPER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
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

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), image_helper);
}

#endif //TEST_SERVICE_INPUT_HPP
