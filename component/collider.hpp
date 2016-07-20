#ifndef GAME_CORE_ENTITY_COMPONENT_COLLIDER_HPP
#define GAME_CORE_ENTITY_COMPONENT_COLLIDER_HPP

#include <typeindex>
#include "common/glm.hpp"

// @TODO : Mass calcultations based on volume and material density

namespace game{

	enum class Shape{BOX, CIRCLE};

	struct Collider{

		bool sleeping;
		bool is_static;

		float mass;
		float inv_mass;
		float weight;
		float restitution_factor;
		float gravity;

		Shape shape_type;
		glm::vec3 target_velocity;

		// Helper methods
		Collider();

		// Caution, use this method instead of changing the mass directly
		void SetMass(float mass);
	};
}

#endif // GAME_CORE_ENTITY_COMPONENT_COLLIDER_HPP
