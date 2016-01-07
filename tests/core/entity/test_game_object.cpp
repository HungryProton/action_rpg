#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/component/texture.hpp"
#include "core/entity/game_object.hpp"
#include "core/game/game.hpp"

namespace game{

    const lest::test game_objects[] = {

			SCENARIO("GameObjects should allow basic operations on them"){

				GIVEN("an empty GameObject with nothing attached on it"){
					GameObject* game_object = new GameObject();

					WHEN("a component is created with the game object as parameter"){
						Texture* initial_texture = new Texture("../data/characters/female/female_1.png", game_object);

						THEN("the component should be attached to the game object"){
							EXPECT(initial_texture->is_attached == true);
						}
						THEN("game object's component count should have increased"){
							int count = game_object->GetAllComponents().size();
							EXPECT(count == 1);
						}
						THEN("we should be able to retrieve the attached component"){
							Texture* attached_texture = game_object->GetComponent<Texture>();
							EXPECT(attached_texture == initial_texture);
						}

						game_object->DetachAndDestroyComponent(initial_texture);
					}

          delete game_object;
				}
			}
    };

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), game_objects);
}
