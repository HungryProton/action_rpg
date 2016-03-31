#ifndef GAME_CORE_COMPONENT_SPRITE_CUSTOMISATION_HPP
#define GAME_CORE_COMPONENT_SPRITE_CUSTOMISATION_HPP

#include <map>
#include "component.hpp"

namespace game{

	struct SpriteCustomization : public Component{
		std::map<int, GameObject*> parts;	// Store a part and its "z_index"

		SpriteCustomization();
		SpriteCustomization(GameObject*);
		SpriteCustomization(SpriteCustomization*);
		virtual SpriteCustomization* Clone();
		virtual void Update();
		void AddPart(std::string, int);
		void AddPart(GameObject*, int);

		private:
			bool init_done;
	};
}

#endif //GAME_CORE_COMPONENT_SPRITE_CUSTOMISATION_HPP
