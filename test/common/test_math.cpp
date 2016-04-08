#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/math.hpp"

namespace game{

	const lest::test math[] = {

		SCENARIO("Clamp function should limit a number within bounds"){
			int min = 10;
			int max = 50;

			GIVEN("a number greater than the maximal value"){
				int number = 140;

				THEN("it should return the maximal value"){
					EXPECT(Math::clamp(number, min, max) == max);
				}
			}
			GIVEN("a number smaller than the minimal value"){
				int number = 1;

				THEN("it should return the minimal value"){
					EXPECT(Math::clamp(number, min, max) == min);
				}
			}
			GIVEN("a number within the bounds"){
				int number = 42;

				THEN("it should return the given number"){
					EXPECT(Math::clamp(number, min, max) == number);
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), math);
}
