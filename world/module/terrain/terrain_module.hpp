#ifndef GAME_WORLD_MODULE_TERRAIN_GENERATOR_HPP_
#define GAME_WORLD_MODULE_TERRAIN_GENERATOR_HPP_

#include <map>
#include "terrain.hpp"
#include "common/random.hpp"

namespace game{

	enum class CellType{ROCK, GRASS, DIRT};

	struct CellData{
		CellType type;
		std::string path;
		float probability;
	};

	struct CellItem{
		std::string path;
		float radius;
		std::map<CellType, float> affinity;
	};

	class TerrainModule{
		public:
			TerrainModule();
			Terrain Generate(double);

		private:
			void RunSimulation(int);
			bool OccupationStep(int, int);
			CellType TypeStep(int, int);
			void CellTypeStep(int, int);
			int CountAliveNeighbors(int, int);
			Entity CreateCell(int, int);
			void PlaceObstacles(Terrain);
			Entity CreateRandomObstacle(int, int);
			Entity CreateObstacle(std::string, float radius, int, int);

			void FillInitialStates();
			void FillCellData();
			void FillCellItems();
			CellType GetRandomCellType();
			std::string GetPathForCell(CellType);

			int width_;
			int height_;
			int death_limit_;	// amount of alive neighbors to kill a cell
			int birth_limit_; // amount of alive neighbors to create a cell
			int step_count_;
			float chance_to_start_alive_;
			float chance_of_z_displacement_;

			std::vector<std::vector<bool>> occupation_map_;
			std::vector<std::vector<CellType>> type_map_;
			std::vector<CellData> cell_data_;
			std::vector<CellItem> cell_items_;

			RealGenerator random_;
	};
}

#endif //GAME_WORLD_MODULE_TERRAIN_GENERATOR_HPP_
