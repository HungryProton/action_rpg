#ifndef GAME_WORLD_MODULE_ARCHITECTURE_HPP_
#define GAME_WORLD_MODULE_ARCHITECTURE_HPP_

#include <vector>
#include "building.hpp"
#include "wall_generator.hpp"

namespace game{

	class ArchitectureModule{
		public:
			std::vector<Building> Generate(double);

		private:
			WallGenerator wall_generator_;
	};
}

#endif //GAME_WORLD_MODULE_ARCHITECTURE_HPP_
