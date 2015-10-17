#ifndef TEST_ENTITY_COMPONENTS_HPP
#define TEST_ENTITY_COMPONENTS_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/entity/component/texture.hpp"
#include "core/entity/gameobject/game_object.hpp"
#include "core/game/game.hpp"

namespace game{

    const lest::test game_objects[] = {

			SCENARIO("GameObjects should allow duplication"){

				GIVEN("a GameObject with components attached on"){

					GameObject* game_object = new GameObject();
					Texture* texture = new Texture(game_object);

					WHEN("a duplicate is requested"){

						THEN("it should return a copy of the object and its components"){
							
						}
					}
				}
			}
    };

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), game_objects);
}

#endif //TEST_TOOLS_LOGGER_HPP
