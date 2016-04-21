#include "context_controller.hpp"
#include "common/logger.hpp"

namespace game{

	ContextController::ContextController(){
		this->configuration_file_path_ = "settings.ini";
		context_validity_ = false;
	}

	ContextController::~ContextController(){
		if(!IsContextValid()){ return; }
	}

	void ContextController::Initialize(){
		context_validity_ = InitializeGLFW() || InitializeOpenGL();
	}

	int ContextController::InitializeGLFW(){
		glfwSetErrorCallback(ContextController::GLFWErrorCallback);
		if(!glfwInit()){
			LOG(ERROR) << "GLFW initialization failed" << std::endl;
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window_ = glfwCreateWindow(1366, 768, "ActionRPG", NULL, NULL);
		glfwMakeContextCurrent(window_);
		glfwSwapInterval(0);
		return 0;
	}

	int ContextController::InitializeOpenGL(){
		glewExperimental=GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err){
			LOG(ERROR) << "GlewInit failed" << std::endl;
			LOG(ERROR) << glewGetErrorString(err) << std::endl;
			return 1;
		}

		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glClearColor(0.67, 0.84, 0.90, 1);
		return 0;
	}

	int ContextController::LoadConfigurationFromFile(){
		return 1;
	}

	GLFWwindow* ContextController::GetWindow(){
		return window_;
	}

	bool ContextController::IsContextValid(){
		return context_validity_;
	}

	void ContextController::GLFWErrorCallback(int error, const char* description){
		LOG(ERROR) << "A GLFW error occured : " << error << ":" << description << std::endl;
	}
}
