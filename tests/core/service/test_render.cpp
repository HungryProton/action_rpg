#ifndef TEST_SERVICE_RENDER_HPP
#define TEST_SERVICE_RENDER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
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

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), render);
}

#endif //TEST_TOOLS_LOGGER_HPP
