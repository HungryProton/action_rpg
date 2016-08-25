#ifndef GAME_COMPONENT_POINT_LIGHT_HPP_
#define GAME_COMPONENT_POINT_LIGHT_HPP_

#include "common/glm.hpp"

namespace game{

	struct PointLight{
		glm::vec3 color;
		float power;

		PointLight();
		PointLight(glm::vec3);
		PointLight(float);
		PointLight(float, glm::vec3);
	};
}

#endif //GAME_COMPONENT_POINT_LIGHT_HPP_
