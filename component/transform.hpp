#ifndef GAME_CORE_ENTITY_COMPONENT_TRANSFORM_HPP
#define GAME_CORE_ENTITY_COMPONENT_TRANSFORM_HPP

#include <glm/glm.hpp>
#include "component.hpp"

namespace game{

	class GameObject;

	/** \brief Define the gameObject position, Rotation, scale, and velocity
	 *
	 *	Will be used by other systems ( like Physic, Render ...).
	 *	note that x represents the horizontal position,
	 *	y represents the deepness, and z represent the
	 *	vertical position.
	 */
	struct Transform : public Component{

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 velocity;
		glm::vec3 target_velocity;

		// ---- Helper Methods ----
		Transform();
		virtual ~Transform();
		Transform(unsigned long);
		Transform(Transform*);
		virtual Transform* Clone();
		void dbg_display();

		private:
			glm::vec3 previous_position;
	};
}

#endif // GAME_CORE_ENTITY_COMPONENT_TRANSFORM_HPP
