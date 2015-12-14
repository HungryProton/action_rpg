#ifndef GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP
#define GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "component.hpp"

namespace game{
	struct Camera : public Component {

		glm::mat4 Projection;
		glm::mat4 View;

		// ----- Helper methods -----
		Camera();
		Camera(GameObject*);
	};
}
#endif //GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP
