#ifndef GAME_WORLD_MODULE_ARCHITECTURE_WALL_GENERATOR_HPP_
#define GAME_WORLD_MODULE_ARCHITECTURE_WALL_GENERATOR_HPP_

#include <vector>
#include <string>
#include "common/glm.hpp"
#include "common/random.hpp"
#include "ecs/entity/entity.hpp"

/*
 * The module generates the walls of a single building.
 * It first generate the positions of the walls on a 2D grid, find
 * the most appropriate place to place a door and some windows, a return
 * a vector containing the walls.
 */

namespace game{

	struct Wall{
		glm::vec2 relative_grid_position;
		Entity entity;
	};

	struct WallParameters{
		std::string base_directory;
		glm::ivec2 minimum_dimensions;
		glm::ivec2 maximum_dimensions;
		// Add something like "Dimensions distribution" maybe?
		float symmetrical_probability;
		glm::vec3 building_position;
	};

	class WallGenerator{
		public:
			WallGenerator();
			std::vector<Wall> Generate(double);
			void SetParameters(WallParameters);

		protected:
			void GenerateFoundationsLayout();
			std::vector<Wall> PlaceWalls();

			Wall GetWall(int, int, int, bool);
			Wall GetWall(int, int, int, bool, bool);

			void AddSquare(int, int, unsigned int, unsigned int);
			void SubstractSquare(int, int, unsigned int, unsigned int);

			IntGenerator random_;
			WallParameters parameters_;
			std::vector<std::vector<int>> foundations_;
	};
}

#endif //GAME_WORLD_MODULE_ARCHITECTURE_WALL_GENERATOR_HPP_
