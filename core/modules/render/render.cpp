#include <cstdlib>
#include "tools/logger.hpp"
#include "render.hpp"

namespace game{

    Render::Render(){
        // Default graphics parameters
        this->window_ = nullptr;
        this->game_name_ = "Action RPG";
        this->opengl_major_version_ = 3;
        this->opengl_minor_version_ = 3;
        this->x_resolution_ = 1440;
        this->y_resolution_ = 900;
        this->antialiasing_level_ = 4;
    }

    Render::~Render(){
        glfwTerminate();
        glfwDestroyWindow(this->window_);
    }

    void Render::HandleMessage(Message msg){
        //log(INFO) << "Processing message " << msg << std::endl;
    }

    void Render::Run(){
        log(INFO) << "Render process method was called !!!!!!! " << std::endl;
        this->LoadParametersFromFile("config/system.conf"); 
        this->CreateWindow();
        this->InitializeOpenGL();
        this->Update();
    }

    void Render::Update(){
        log(INFO) << "called update" << std::endl;
        while(this->module_state_ == RUNNING){
            this->ClearScreen();
        }
    }

    void Render::CreateWindow(){

        glfwInit();

        glfwWindowHint(GLFW_SAMPLES, this->antialiasing_level_); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->opengl_major_version_);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->opengl_minor_version_);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

        this->window_ = glfwCreateWindow( this->x_resolution_,
                                          this->y_resolution_, 
                                          this->game_name_,
                                          NULL, NULL);

        glfwMakeContextCurrent(this->window_);

    }

    void Render::InitializeOpenGL(){
        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if (GLEW_OK != err){
            log(ERROR) << "GlewInit failed for reason : " << 
            glewGetErrorString(err) << std::endl;
        }

        glDepthFunc(GL_LESS);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glAlphaFunc(GL_GREATER, 0.1f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glClearColor(0.3, 0.3, 0.3, 1);

    }

    bool Render::LoadParametersFromFile(std::string file_path){
        log(INFO) << "Reading parameters from " << file_path << std::endl;

        return EXIT_SUCCESS;
    }

    void Render::ClearScreen(){
        glfwSwapBuffers(this->window_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }


}
