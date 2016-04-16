#ifndef GAME_TEST_CONTEXT_UTIL_HPP
#define GAME_TEST_CONTEXT_UTIL_HPP

#include "common/opengl.hpp"
#include "common/logger.hpp"

namespace game{

	class ContextUtil{
		public:
			static void CreateOpenGLContext();
			static void DestroyOpenGLContext();
			static GLFWwindow* GetWindow();

		private:
			static GLFWwindow* window_;
	};
}

#endif //GAME_TEST_CONTEXT_UTIL_HPP
