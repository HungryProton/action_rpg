#ifndef GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP
#define GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "component.hpp"

namespace game{
	struct Camera : public Component {

		glm::mat4 projection;
		glm::mat4 view_projection;
		float fovy;
		float ratio;
		float znear;
		float zfar;
		glm::vec3 target;
		glm::vec3 up;
		bool active;

		// ----- Helper methods -----
		Camera();
		Camera(GameObject*);
		Camera(Camera*);
		virtual Camera* Clone();
		void SetActive();
	};
}
#endif //GAME_CORE_ENTITY_COMPONENT_CAMERA_HPP
