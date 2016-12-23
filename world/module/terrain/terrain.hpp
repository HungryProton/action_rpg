#ifndef GAME_WORLD_MODULE_TERRAIN_HPP_
#define GAME_WORLD_MODULE_TERRAIN_HPP_

#include <vector>
#include "ecs/entity/entity.hpp"

namespace game{

	enum class TerrainState{EMPTY, BASE, OCCUPIED};

	struct Terrain{
		std::vector<Entity> blocks;
		std::vector<std::vector<TerrainState>> map;
	};
}

#endif //GAME_WORLD_MODULE_TERRAIN_HPP_
