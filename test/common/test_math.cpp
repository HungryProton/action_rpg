#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "common/math.hpp"

namespace game{

	SCENARIO("Clamp function should limit a number within bounds"){
		int min = 10;
		int max = 50;

		GIVEN("a number greater than the maximal value"){
			int number = 140;

			THEN("it should return the maximal value"){
				REQUIRE(Math::clamp(number, min, max) == max);
			}
		}
		GIVEN("a number smaller than the minimal value"){
			int number = 1;

			THEN("it should return the minimal value"){
				REQUIRE(Math::clamp(number, min, max) == min);
			}
		}
		GIVEN("a number within the bounds"){
			int number = 42;

			THEN("it should return the given number"){
				REQUIRE(Math::clamp(number, min, max) == number);
			}
		}
	}
}
