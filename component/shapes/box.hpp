#ifndef GAME_COMPONENT_BOX_HPP
#define GAME_COMPONENT_BOX_HPP

#include <glm/glm.hpp>
#include "shape.hpp"

namespace game{

	class GameObject;

	struct Box : public ShapeComponent{
		float width;
		float height;

		// ---- Helper methods ----
		// Not specifying size upon creations makes the Render system
		// define an automatic size according to texture size.
		// 256 pixels = 1 meter
		Box();
		Box(Entity);
		Box(float, float, Entity);
		Box(Box*);
		virtual Box* Clone();
		void SetDimensions(glm::vec2);
		void SetDimensions(float, float);
	};
}



#endif // GAME_COMPONENT_BOX_HPP
