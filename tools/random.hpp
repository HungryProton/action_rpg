#ifndef GAME_TOOL_RANDOM_HPP
#define GAME_TOOL_RANDOM_HPP

#include <random>

namespace game{

	class Random{
		public:
			static int Range(int, int);
			static int NextInt();

		private:
			static std::default_random_engine generator_;
			static std::uniform_int_distribution<int> distribution_;
	};
}
#endif //GAME_TOOL_RANDOM_HPP
