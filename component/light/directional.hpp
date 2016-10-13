#ifndef GAME_COMPONENT_DIRECTIONAL_LIGHT_HPP_
#define GAME_COMPONENT_DIRECTIONAL_LIGHT_HPP_

#include "common/glm.hpp"

namespace game{

	struct DirectionalLight{
		glm::vec3 direction;
		glm::vec3 color;
		float power;

		DirectionalLight();
		DirectionalLight(glm::vec3, float);
		DirectionalLight(glm::vec3, float, glm::vec3);
	};
}

#endif //GAME_COMPONENT_DIRECTIONAL_LIGHT_HPP_
