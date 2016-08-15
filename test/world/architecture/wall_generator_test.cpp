#include "deps/catch.hpp"
#include "world/module/architecture/wall_generator.hpp"

namespace game{

	class WallGeneratorStub : public WallGenerator{
		public:
			WallGeneratorStub() : WallGenerator(){}
			std::vector<std::vector<int>> GetFoundations(){ return foundations_; }
			void GenerateFoundationsLayout(){ WallGenerator::GenerateFoundationsLayout(); }

	};

	SCENARIO("The wall generator should produce a grid representing the walls"){
		GIVEN("a wall generator"){
			WallGeneratorStub generator;

			WHEN("we generate the layout"){
				generator.GenerateFoundationsLayout();

				THEN("it should fill the grid with squares"){

				}
			}
		}
	}

	SCENARIO("The wall generator can output a closed loop of walls"){

		GIVEN("a wall generator"){
			WallGeneratorStub generator;

			WHEN("we setup and start the generator, it should return a collection of walls"){

			}
		}
	}
}
