#ifndef GAME_WORLD_MODULE_TERRAIN_GENERATOR_HPP_
#define GAME_WORLD_MODULE_TERRAIN_GENERATOR_HPP_

#include "terrain.hpp"
#include "common/random.hpp"

namespace game{

	class TerrainModule{
		public:
			TerrainModule();
			Terrain Generate(double);

		private:
			std::vector<std::vector<bool>> RunSimulation(int, std::vector<std::vector<bool>> map);
			int CountAliveNeighbors(std::vector<std::vector<bool>>, int, int);
			Entity CreateCell(int, int);

			RealGenerator random_;

			int width_;
			int height_;
			int death_limit_;	// amount of alive neighbors to kill a cell
			int birth_limit_; // amount of alive neighbors to create a cell
			int step_count_;
			float chance_to_start_alive_;
			float chance_of_z_displacement_;
	};
}

#endif //GAME_WORLD_MODULE_TERRAIN_GENERATOR_HPP_
