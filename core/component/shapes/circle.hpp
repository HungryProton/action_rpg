#ifndef GAME_COMPONENT_CIRCLE_HPP
#define GAME_COMPONENT_CIRCLE_HPP

#include "../component.hpp"

namespace game{

	struct Circle : public Component{
		float radius;
		int vertex_amount; // Amount of vertices that compose the circle
							 // The higher the better resolution

		// ----- Helper methods -----
		Circle();
		Circle(GameObject*);
		Circle(float, GameObject*);
		Circle(float, int, GameObject*);
		Circle(Circle*);
		virtual Circle* Clone();
	};
}

#endif //GAME_COMPONENT_CIRCLE_HPP
