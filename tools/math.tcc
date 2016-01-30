#include <algorithm>
#include "math.hpp"

namespace game{

	template<class T>
	T Math::clamp(T n, T lower, T upper){
		return std::max(lower, std::min(n, upper));
	}
}
