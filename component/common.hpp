#ifndef GAME_CORE_COMPONENT_COMMON_HPP
#define GAME_CORE_COMPONENT_COMMON_HPP

#include "common/opengl.hpp"
#include  "ecs/entity/entity.hpp"

namespace game{
	enum class SystemEvent{NEW_COMPONENT, CHANNEL_CHANGED};
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

		bool IsObjectWithin(Entity);
	};

	Direction GetDirectionFromVector(glm::vec3);
}

#endif //GAME_CORE_COMPONENT_COMMON_HPP

