#ifndef GAME_SYSTEM_DEBUG_STATS_HPP_
#define GAME_SYSTEM_DEBUG_STATS_HPP_

#include "system/system.hpp"

namespace game{

	class DebugStats : public System{
		public:
			DebugStats();
			~DebugStats();

		protected:
			void BeforeUpdate();
	};
}

#endif //GAME_SYSTEM_DEBUG_STATS_HPP_
