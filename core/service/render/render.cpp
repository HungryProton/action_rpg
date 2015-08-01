#include <iostream>
#include "render.hpp"
#include "tools/logger.hpp"
#include "helpers/image_helper.hpp"

namespace game{

    Render::Render(){
        this->window_ = nullptr;
        this->InitializeHelpers();
        this->InitializeGLFW();
        this->InitializeOpenGL();
    }

    Render::~Render(){
        this->ClearMemory();
    }

    void Render::ClearMemory(){
        auto it = this->helpers_.begin();

        while( it != this->helpers_.end() ){
            Service* service = (*it);
            Locator::Remove(service);
            it++;
        }
    }

    void Render::InitializeGLFW(){
        glfwInit();
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
            log(INFO) << "GlewInit failed" << std::endl;
            log(INFO) << glewGetErrorString(err) << std::endl;
        }

        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(0.3, 0.3, 0.3, 1);
    }

    void Render::InitializeHelpers(){
        this->RegisterHelper<ImageHelper>();
    }

    void Render::Update(){
        glfwSwapBuffers(this->window_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    GLFWwindow* Render::GetWindow(){
        return this->window_;
    }
}
