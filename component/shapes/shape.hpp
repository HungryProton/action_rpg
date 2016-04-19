#ifndef GAME_COMPONENT_SHAPE_HPP
#define GAME_COMPONENT_SHAPE_HPP

#include "../component.hpp"

namespace game{

	class ShapeComponent : public Component{
		public:
			ShapeComponent() : Component(){}
			virtual ~ShapeComponent() = 0;
	};
}

#endif //GAME_COMPONENT_SHAPE_HPP
