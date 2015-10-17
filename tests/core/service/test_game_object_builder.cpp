#ifndef TEST_SERVICE_IMAGE_HELPER_HPP
#define TEST_SERVICE_IMAGE_HELPER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/service/builder/game_object_builder.hpp"

namespace game{

	const lest::test game_object_builder[] = {

		SCENARIO("GameObjectBuilder should create and return GameObjects"){

			GIVEN("that the GameObjectBuilder operated under normal conditions"){

				GameObjectBuilder builder;

				WHEN("a new blank object is requested"){

					GameObject* game_object = nullptr;
					game_object = builder.CreateBlank();

					THEN("it should return a valid GameObject"){
						EXPECT(game_object != nullptr);
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), game_object_builder);
}

#endif //TEST_SERVICE_INPUT_HPP
