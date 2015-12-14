#ifndef GAME_CORE_ENTITY_COMPONENT_COLLIDER_HPP
#define GAME_CORE_ENTITY_COMPONENT_COLLIDER_HPP

#include <typeindex>
#include "component.hpp"

// @TODO : Mass calcultations based on volume and material density

namespace game{

	struct Collider : public Component{

		std::type_index shape_type;
		bool sleeping;
		bool is_static;

		float mass;
		float inv_mass;
		float weight;
		float restitution_factor;

		float gravity;

		// Helper methods
		Collider();
		Collider(GameObject*);

		void SetMass(float mass);
	};
}

#endif // GAME_CORE_ENTITY_COMPONENT_COLLIDER_HPP
