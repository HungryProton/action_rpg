#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

namespace game{

	enum State{ UNINITIALIZED, RUNNING, EXITING };

	class Game{
		public:
			static void Initialize();
			static void Play();
			static void Stop();

			static State GetState();

		private:
			static void ClearMemory();
			static void AdjustFrameRate();

			static State state_;
			static float frame_duration_target_;
	};
}

#endif //GAME_HPP
