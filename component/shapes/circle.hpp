#ifndef GAME_COMPONENT_CIRCLE_HPP
#define GAME_COMPONENT_CIRCLE_HPP

#include "shape.hpp"

namespace game{

	struct Circle : public ShapeComponent{
		float radius;
		int vertex_amount; // Amount of vertices that compose the circle
											 // The higher the better resolution

		// ----- Helper methods -----
		Circle();
		Circle(Entity);
		Circle(float, Entity);
		Circle(float, int, Entity);
		Circle(Circle*);
		virtual Circle* Clone();
	};
}

#endif //GAME_COMPONENT_CIRCLE_HPP
