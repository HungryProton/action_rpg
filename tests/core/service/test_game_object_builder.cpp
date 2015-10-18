#ifndef TEST_SERVICE_IMAGE_HELPER_HPP
#define TEST_SERVICE_IMAGE_HELPER_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/service/builder/game_object_builder.hpp"
#include "core/entity/component/texture.hpp"

namespace game{

	const lest::test game_object_builder[] = {

		SCENARIO("GameObjectBuilder should create and return GameObjects"){
			GameObjectBuilder builder;
			GameObject* game_object = nullptr;

			GIVEN("No presets were registered to the GameObjectBuilder"){

				WHEN("a new blank object is requested"){
					game_object = builder.CreateBlank();

					THEN("it should return a valid GameObject"){
						EXPECT(game_object != nullptr);
					}
				}

				WHEN("a preset is requested"){
					game_object = builder.CreateFromPreset("Player");

					THEN("it should return a null pointer"){
						EXPECT(game_object == nullptr);
					}
				}
			}

			GIVEN("Some presets were registered to the GameObjectBuilder"){
				GameObject* sprite = builder.CreateBlank();
				new Texture("tests/resources/1.png", sprite);

				GameObject* other_sprite = builder.CreateBlank();
				new Texture("tests/resources/1.png", other_sprite);

				builder.RegisterPreset("Player", sprite);
				builder.RegisterPreset("Ennemy", other_sprite);

				WHEN("an existing preset is requested"){
					game_object = builder.CreateFromPreset("Player");

					THEN("it should return a valid gameObject and the right components"){
						EXPECT(game_object != nullptr);
						EXPECT(game_object->GetComponent<Texture>() != nullptr);
					}
				}

				WHEN("an unknown preset is requested"){
					game_object = builder.CreateFromPreset("UltimateBoss");

					THEN("it should return a null pointer"){
						EXPECT(game_object == nullptr);
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), game_object_builder);
}

#endif //TEST_SERVICE_INPUT_HPP
