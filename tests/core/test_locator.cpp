#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/service/render/render.hpp"
#include "core/locator/locator.hpp"

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

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), locator);
}
