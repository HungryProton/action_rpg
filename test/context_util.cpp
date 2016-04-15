#include "context_util.hpp"

namespace game{

	void ContextUtil::CreateOpenGLContext(){
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window_ = glfwCreateWindow( 1366, 768, "Game", NULL, NULL);
		glfwMakeContextCurrent(window_);

		glewExperimental=GL_TRUE;
		GLenum err = glewInit();
		glGetError(); // Silence an error from glew
		if (GLEW_OK != err){
			LOG(ERROR) << "GlewInit failed" << std::endl;
			LOG(ERROR) << glewGetErrorString(err) << std::endl;
		}
	}

	void ContextUtil::DestroyOpenGLContext(){
		glfwDestroyWindow(window_);
		glfwTerminate();
	}

	GLFWwindow* ContextUtil::window_;
}
