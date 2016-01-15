#include "common.hpp"
#include "tools/logger.hpp"
#include "core/messaging/message_bus.hpp"

namespace game{

	void Common::CreateOpenGLContext(){
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window_ = glfwCreateWindow( 1440, 900, "Game", NULL, NULL);
		glfwMakeContextCurrent(window_);

		glewExperimental=GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err){
			LOG(ERROR) << "GlewInit failed" << std::endl;
			LOG(ERROR) << glewGetErrorString(err) << std::endl;
		}
	}

	void Common::DestroyOpenGLContext(){
		glfwDestroyWindow(window_);
		glfwTerminate();
	}

	void Common::SendInputMessage(Command command){
		InputMessage message;
		message.status = KEY_PRESSED;
		message.command = command;
		MessageBus::Push(message);
	}

	GLFWwindow* Common::window_;
}
