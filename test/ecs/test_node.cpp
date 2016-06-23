#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "ecs/node.hpp"
#include "common/logger.hpp"

namespace game{

	const lest::test node[] = {
		SCENARIO("It should allow systems to match concerned entities"){

			GIVEN("registered signatures and usefull entities"){

				WHEN("components matching a given signature are requested"){

					THEN("it should return the appropriate entities"){

					}
					THEN("it should not return entities that does not match"){

					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), node);
}
