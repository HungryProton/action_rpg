#include "random.hpp"

namespace game{

	int Random::NextInt(){
		return distribution_(generator_);
	}

	int Random::Range(int begin, int end){
		std::uniform_int_distribution<int> distribution(begin, end);
		return distribution(generator_);
	}

	std::default_random_engine Random::generator_;
	std::uniform_int_distribution<int> Random::distribution_(1,100);
}
