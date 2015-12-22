#ifndef GAME_TOOLS_TIME_HPP
#define GAME_TOOLS_TIME_HPP

#include "opengl.hpp"

namespace game{

	class Time{
		public:
			static void SetFrameStartTime(double);
			static float GetDeltaTime();

		private:
			static float frame_start_time_;
	};
}

#endif //GAME_TOOLS_TIME_HPP
