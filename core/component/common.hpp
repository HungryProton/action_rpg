#ifndef GAME_CORE_COMPONENT_COMMON_HPP
#define GAME_CORE_COMPONENT_COMMON_HPP

#include "tools/opengl.hpp"
#include  "core/entity/game_object.hpp"

namespace game{
	enum class Direction{N,S,E,W,NE,NW,SE,SW,LAST};

	struct Vertex{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coords;
	};

	// Areas definitions
	enum class AreaType{RECTANGLE, CIRCLE, CONE};
	struct Area{
		glm::vec3 position;
		glm::vec2 size;
		float radius;
		float opening_angle;
		float orientation_angle;
		AreaType type;

		bool IsObjectWithin(GameObject*);
	};
}

#endif //GAME_CORE_COMPONENT_COMMON_HPP

