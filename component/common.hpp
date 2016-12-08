#ifndef GAME_CORE_COMPONENT_COMMON_HPP
#define GAME_CORE_COMPONENT_COMMON_HPP

#include "common/opengl.hpp"
#include  "ecs/entity/entity.hpp"

namespace game{

	// First value appears behind, Last value appears on top
	enum class EquipmentType{NONE, BODY, WEAPON, HEAD};
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

	Direction GetDirectionFromAngle(float angle);
	Direction GetDirectionFromVector(glm::vec3);
	std::string DirectionToString(Direction);
}

#endif //GAME_CORE_COMPONENT_COMMON_HPP

