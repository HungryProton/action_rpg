#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/service/render/render.hpp"
#include "core/locator/locator.hpp"

namespace game{

    const lest::test locator[] = {

			SCENARIO("Service locator should provide access to registered services"){

				GIVEN("a service locator and a service provided to the locator"){
					Render* render = new Render();
					Locator::Provide(render);

					WHEN("a registered service is requested from the locator"){
            Render* render_from_locator = Locator::Get<Render>();

						THEN("it should return a pointer to the proper service"){
							EXPECT( render_from_locator == render );
						}
					}
					WHEN("a unregistered service is requested from the locator"){
						ImageHelper* image_helper_service = Locator::Get<ImageHelper>();

						THEN("it should return a null pointer"){
							EXPECT(image_helper_service == nullptr);
						}
					}
					delete render;
				}
			}
    };

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), locator);
}
