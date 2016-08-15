#include "random.hpp"
#include <ctime>

namespace game{

	int Random::NextInt(int count){
		return int_distribution_(generator_)%(count+1);
	}

	float Random::NextFloat(float count){
		return real_distribution_(generator_)*count;
	}

	IntGenerator::IntGenerator(double seed) : engine(seed){}

	int IntGenerator::Next(int lower, int upper){
		std::uniform_int_distribution<int> distribution(lower, upper);
		return distribution(engine);
	}

	int IntGenerator::Next(int upper){
		return Next(0, upper);
	}

	RealGenerator::RealGenerator(double seed) : engine(seed){}

	float RealGenerator::Next(float lower, float upper){
		std::uniform_real_distribution<float> distribution(lower, upper);
		return distribution(engine);
	}

	float RealGenerator::Next(float upper){
		return Next(0, upper);
	}

	std::default_random_engine Random::generator_(time(NULL));
	std::uniform_real_distribution<float> Random::real_distribution_(0.f,1.f);
	std::uniform_int_distribution<int> Random::int_distribution_(0,100);
}
