#ifndef GAME_SYSTEM_SIMPLE_MOTION_HPP_
#define GAME_SYSTEM_SIMPLE_MOTION_HPP_

#include "system/system.hpp"

namespace game{

	class SimpleMotionSystem : public System{
		public:
			SimpleMotionSystem();

		protected:
			void OnUpdate(Entity);
	};
}

#endif //GAME_SYSTEM_SIMPLE_MOTION_HPP_
