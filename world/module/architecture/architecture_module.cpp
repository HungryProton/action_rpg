#include "architecture_module.hpp"
#include "wall_generator.hpp"

namespace game{

	std::vector<Building> ArchitectureModule::Generate(double seed){
		std::vector<Building> buildings;

		WallGenerator wall_generator;
		WallParameters parameters;
		parameters.base_directory = "../data/environment/architecture/building/type_01/";
		parameters.maximum_dimensions = glm::ivec2(10, 10);
		parameters.minimum_dimensions = glm::ivec2(4, 4);
		parameters.building_position = glm::vec3(0, 0, 0);
		parameters.symmetrical_probability = 0.5;

		wall_generator.SetParameters(parameters);
		wall_generator.Generate(seed);

		return buildings;
	}
}
