#ifndef GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP
#define GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP

#include "common/glm.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	struct Camera{
		glm::mat4 projection;
		glm::mat4 view;
		float fovy;
		float ratio;
		float znear;
		float zfar;
		glm::vec3 target;
		glm::vec3 up;
		bool active;

		Entity parent;

		// ----- Helper methods -----
		Camera();
		void SetActive();
	};
}
#endif //GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP
