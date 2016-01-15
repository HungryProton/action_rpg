#ifndef GAME_TOOL_RANDOM_HPP
#define GAME_TOOL_RANDOM_HPP

#include <random>

namespace game{

	class Random{
		public:
			static int NextInt(int count=100);
			static float NextFloat(float count=1.f);

		private:
			static std::default_random_engine generator_;
			static std::uniform_real_distribution<float> real_distribution_;
			static std::uniform_int_distribution<int> int_distribution_;
	};
}
#endif //GAME_TOOL_RANDOM_HPP
