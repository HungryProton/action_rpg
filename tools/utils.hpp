#ifndef GAME_TOOLS_UTILS_HPP
#define GAME_TOOLS_UTILS_HPP

#include "core/entity/game_object.hpp"
#include "core/component/transform.hpp"

namespace game{

	class Utils{
		public:
			static float Distance(GameObject*, GameObject*);
	};
}

#endif //GAME_TOOLS_UTILS_HPP
