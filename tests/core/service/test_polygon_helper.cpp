#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "core/service/helper/polygon_helper.hpp"

namespace game{

    const lest::test polygon_helper[] = {

			SCENARIO("The library should allow basic polygons operations"){

				GIVEN("an initial collection of floats representing a valid polygon"){

					WHEN("the converter from floats to vertices is called"){

						THEN("it should return a valid set of vertices"){

						}
					}
					WHEN("the converter from vertices to filled polygon is called"){

						THEN("it should return a valid polygon object"){

						}
					}
					WHEN("the converter from polygon to OpenGL data is called"){

						THEN("it should modify the vertex/index/texture arrays"){

						}
					}
					WHEN("the converter from multiple polygons to GL data is called"){

						THEN("it should modify the vertex/index/texture arrays"){

						}
					}
				}
				GIVEN("an invalid collection of floats"){

					WHEN("any converter is called"){

						THEN("the validation tests should interrupt the task and throw an exception"){

						}
					}
				}
			}

    };

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), polygon_helper);
}
