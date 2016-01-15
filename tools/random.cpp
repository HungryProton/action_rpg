#include "random.hpp"

namespace game{

	int Random::NextInt(){
		return (int)NextFloat();
	}

	float Random::NextFloat(){
		return distribution_(generator_);
	}

	float Random::Range(int begin, int end){
		std::uniform_real_distribution<float> distribution(begin, end);
		return distribution(generator_);
	}

	std::default_random_engine Random::generator_;
	std::uniform_real_distribution<float> Random::distribution_(1.f,100.f);
}
