#ifndef GAME_CORE_COMPONENT_COMMON_HPP
#define GAME_CORE_COMPONENT_COMMON_HPP

#include "tools/opengl.hpp"

namespace game{
	enum class Direction{N,S,E,W,NE,NW,SE,SW,LAST};

	struct Vertex{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coords;
	};
}

#endif //GAME_CORE_COMPONENT_COMMON_HPP

