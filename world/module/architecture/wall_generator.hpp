#ifndef GAME_WORLD_MODULE_ARCHITECTURE_WALL_GENERATOR_HPP_
#define GAME_WORLD_MODULE_ARCHITECTURE_WALL_GENERATOR_HPP_

#include <vector>
#include "common/glm.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	struct Wall{
		glm::vec2 relation_grid_position;
		Entity wall_entity;
	};

	class WallGenerator{
		public:
			std::vector<Wall> Generate(double);
	};
}

#endif //GAME_WORLD_MODULE_ARCHITECTURE_WALL_GENERATOR_HPP_
