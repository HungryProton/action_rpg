#include <algorithm>
#include "math.hpp"

namespace game{

	template<class T>
	T Math::clamp(T n, T lower, T upper){
		return std::max(lower, std::min(n, upper));
	}

	template<class T>
	T Math::lerp(T a, T b, T f){
		return a + f * (b - a);
	}
}
