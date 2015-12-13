#include <iostream>
#include "render.hpp"
#include "tools/logger.hpp"
#include "core/game/game.hpp"

namespace game{

    Render::Render(){
        this->window_ = nullptr;
        this->InitializeGLFW();
        this->InitializeOpenGL();
    }

    Render::~Render(){
        this->ClearMemory();
    }

    void Render::ClearMemory(){
			if(this->window_){
				glfwDestroyWindow(this->window_);
				glfwTerminate();
			}
    }

    void Render::InitializeGLFW(){
				LOG(INFO) << "Initializing GLFW" << std::endl;
				glfwSetErrorCallback(Render::GLFWErrorCallback);
        if(!glfwInit()){
					LOG(ERROR) << "GLFW initialization failed" << std::endl;
					Game::Stop();
					return;
				}
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        this->window_ = glfwCreateWindow( 1440, 900, "Game", NULL, NULL);
        glfwMakeContextCurrent(this->window_);
    }

    void Render::InitializeOpenGL(){
        glewExperimental=GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err){
            LOG(ERROR) << "GlewInit failed" << std::endl;
            LOG(ERROR) << glewGetErrorString(err) << std::endl;
        }

        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(0.3, 0.3, 0.3, 1);
    }

    void Render::Update(){
        glfwSwapBuffers(this->window_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    GLFWwindow* Render::GetWindow(){
        return this->window_;
    }

		void Render::GLFWErrorCallback(int error, const char* description){
			LOG(ERROR) << "A GLFW error occured : " << error << ":" << description << std::endl;
		}
}
