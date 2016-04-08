#ifndef CORE_TOOLS_MATH_HPP
#define CORE_TOOLS_MATH_HPP

namespace game{

	class Math{
		public:
			template<class T>
			static T clamp(T, T, T);

			template<class T>
			static T lerp(T, T, T);
	};
}

#include "math.tcc"
#endif //CORE_TOOLS_MATH_HPP
