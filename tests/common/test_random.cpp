#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/random.hpp"

namespace game{

	const lest::test random[] = {

		SCENARIO("Random module should generate integers within the given bounds"){

			GIVEN("a maximum value"){
				int max = 42;

				THEN("the generated numbers should be within [0, max]"){
					bool verified = true;
					for(int i = 0; i < max*2; i++){
						int random_int = Random::NextInt(max);
						if(random_int > max || random_int < 0){
							verified = false;
							break;
						}
					}
					EXPECT(verified == true);
				}
			}
		},

		SCENARIO("Random module should generate floats within the given bounds"){

			GIVEN("a maximum value"){
				float max = 2.f;

				THEN("the generated numbers should be within [0, max]"){
					bool verified = true;
					for(int i = 0; i < 50; i++){
						float random_float = Random::NextFloat(max);
						if(random_float > max || random_float < 0){
							verified = false;
							break;
						}
					}
					EXPECT(verified == true);
				}
			}
		}

	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), random);
}
