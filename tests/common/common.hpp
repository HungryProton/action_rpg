#ifndef GAME_TEST_COMMON_HPP
#define GAME_TEST_COMMON_HPP

#include "tools/opengl.hpp"

namespace game{

	class Common{

		public:
			static void CreateOpenGLContext();
			static void DestroyOpenGLContext();

		private:
			static GLFWwindow* window_;

	};
}

#endif //GAME_TEST_COMMON_HPP
