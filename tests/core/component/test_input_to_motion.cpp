#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/component/input_to_motion.hpp"
#include "core/component/motion.hpp"
#include "tests/common/common.hpp"

namespace game{

	const lest::test input_to_motion[] = {

		SCENARIO("InputToMotion component should affect the Motion component"){

			GIVEN("an InputToMotion and a Motion component attached to a gameObject"){
				GameObject* game_object = new GameObject();
				new Transform(game_object);
				Motion* motion = new Motion(game_object);
				new InputToMotion(game_object);

				WHEN("a MOVE_UP message is broadcasted"){
					float direction_y = motion->direction_.y;
					Common::SendInputMessage(Command::MOVE_UP);
					game_object->Update();

					THEN("The Motion component should have changed"){
						EXPECT(direction_y != motion->direction_.y);
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), input_to_motion);
}
