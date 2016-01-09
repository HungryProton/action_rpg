#ifndef GAME_CORE_ENTITY_COMPONENT_MATERIAL_HPP
#define GAME_CORE_ENTITY_COMPONENT_MATERIAL_HPP

#include "component.hpp"

namespace game{

	enum MaterialPreset{ WOOD, METAL, CONCRETE, EARTH };

	struct Material : public Component{

		// TODO : Add units
		float friction;
		float inflamable_factor;
		float absorbion_factor; // for liquids
		float restitution;
		float density; // In kg/m3


		//----- Helper Methods-----

		Material();
		Material(GameObject*);
		Material(MaterialPreset, GameObject* p = nullptr);
		Material(Material*);
		Material* Clone();
		void UsePreset(MaterialPreset);
	};

}

#endif //GAME_CORE_ENTITY_COMPONENT_MATERIAL_HPP
