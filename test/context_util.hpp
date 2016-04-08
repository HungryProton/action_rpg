#ifndef GAME_TEST_CONTEXT_UTIL_HPP
#define GAME_TEST_CONTEXT_UTIL_HPP

#include "common/opengl.hpp"
#include "common/logger.hpp"

namespace game{
	class ContextUtil{
		public:

			static void CreateOpenGLContext(){
				glfwInit();
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				window_ = glfwCreateWindow( 1366, 768, "Game", NULL, NULL);
				glfwMakeContextCurrent(window_);

				glewExperimental=GL_TRUE;
				GLenum err = glewInit();
				if (GLEW_OK != err){
					LOG(ERROR) << "GlewInit failed" << std::endl;
					LOG(ERROR) << glewGetErrorString(err) << std::endl;
				}
			}

			static void DestroyOpenGLContext(){
				glfwDestroyWindow(window_);
				glfwTerminate();
			}

		private:
			static GLFWwindow* window_;
	};

	GLFWwindow* ContextUtil::window_;
}

#endif //GAME_TEST_CONTEXT_UTIL_HPP
