#ifndef GAME_TOOLS_TIME_HPP
#define GAME_TOOLS_TIME_HPP

#include "opengl.hpp"

namespace game{

	class Time{
		public:
			static void NotifyFrameStart();
			static float GetCurrentTime();	// In seconds
			static float GetPreviousDeltaTime();
			static float GetCurrentFrameAdvance();

		private:
			static float frame_start_time_;
			static float delta_;
	};
}

#endif //GAME_TOOLS_TIME_HPP
