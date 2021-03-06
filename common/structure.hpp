#ifndef GAME_COMMON_STRUCTURE_HPP_
#define GAME_COMMON_STRUCTURE_HPP_

#include <vector>
#include "common/glm.hpp"

namespace game{

	class Structure{
		public:
			template<class T>
			static void Fill2DVector(std::vector<std::vector<T>>*, int, int, T);

			template<class T>
			static void Display2DVector(std::vector<std::vector<T>>*);

			template<class T>
			static void Display2DVectorTranspose(std::vector<std::vector<T>>*);
	};
}

#include "structure.tcc"
#endif //GAME_COMMON_STRUCTURE_HPP_
