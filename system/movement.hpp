#ifndef GAME_SYSTEM_MOVEMENT_HPP_
#define GAME_SYSTEM_MOVEMENT_HPP_

#include "system.hpp"

namespace game{

	class Movement : public System{
		public:
			Movement();
			~Movement();

		protected:
			void OnUpdate(Entity);
	};
}

#endif //GAME_SYSTEM_MOVEMENT_HPP_
