#include "random.hpp"
#include <ctime>

namespace game{

	int Random::NextInt(int count){
		return int_distribution_(generator_)%(count+1);
	}

	float Random::NextFloat(float count){
		return real_distribution_(generator_)*count;
	}

	std::default_random_engine Random::generator_(time(NULL));
	std::uniform_real_distribution<float> Random::real_distribution_(0.f,1.f);
	std::uniform_int_distribution<int> Random::int_distribution_(0,100);
}
