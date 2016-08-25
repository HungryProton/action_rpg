#ifndef GAME_SYSTEM_AI_RANDOM_HPP_
#define GAME_SYSTEM_AI_RANDOM_HPP_

#include "system/system.hpp"

namespace game{

	class RandomAISystem : public System{
		public:
			RandomAISystem();
			~RandomAISystem();

		protected:
			void OnUpdate(Entity);
	};
}

#endif //GAME_SYSTEM_AI_RANDOM_HPP_
