#ifndef GAME_WORLD_ARCHITURECTURE_BUILDING_HPP_
#define GAME_WORLD_ARCHITURECTURE_BUILDING_HPP_

#include <vector>
#include "common/glm.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	struct Building{
		glm::vec2 center;
		bool habitable;
		std::vector<Entity> entities_;	// everything from walls to furniture
	};
}

#endif //GAME_WORLD_ARCHITURECTURE_BUILDING_HPP_
