#include "deps/catch.hpp"
#include "world/module/architecture/architecture_module.hpp"

namespace game{
	bool CheckBuildingValidity(Building*);

	SCENARIO("The architecture module should generate valid structures"){

		GIVEN("a valid module"){
			ArchitectureModule module;

			WHEN("we setup and start the generation of a single house"){

				THEN("it should return a collection of architectural structures containing one house"){
					auto collection = module.Generate(10);
					REQUIRE(collection.size() == 1);

					Building house = collection[0];
					REQUIRE(CheckBuildingValidity(&house));
				}
			}
			WHEN("we setup and start generation for an entire city"){

				THEN("it should return a collection containing many buildings"){

				}
				THEN("the amount of identical buildings should be close to zero"){

				}
			}
		}
	}

	bool CheckBuildingValidity(Building* b){
		if(!b->habitable){	// A ruin (not habitable building) must have at least a few elements
			return b->entities_.size() > 2;
		}

		// The smallest habitable house has at least 4 corners, 3 walls a door
		// and a roof.
		if(b->entities_.size() < 9){ return false; }

		// Make other tests here
		return true;
	}
}
