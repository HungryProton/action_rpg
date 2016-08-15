#ifndef GAME_TOOL_RANDOM_HPP
#define GAME_TOOL_RANDOM_HPP

#include <random>

namespace game{

	// TODO : Make these class templated
	struct RealGenerator{
		std::mt19937 engine;
		float Next(float);
		float Next(float, float);
		RealGenerator(double);
	};

	struct IntGenerator{
		std::mt19937 engine;
		int Next(int);
		int Next(int, int);
		IntGenerator(double);
	};

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
