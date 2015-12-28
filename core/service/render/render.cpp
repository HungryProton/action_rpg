#include <iostream>
#include "render.hpp"
#include "tools/logger.hpp"
#include "core/game/game.hpp"
#include "core/service/helper/buffer_helper.hpp"

namespace game{

	Render::Render(){
		this->window_ = nullptr;
		this->camera_ = nullptr;
		this->InitializeGLFW();
		this->InitializeOpenGL();
		Game::RequestForService<BufferHelper>();
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
		glfwSwapInterval(1);
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

	void Render::ProcessReceivedMessages(){
		for(RenderingIntent intent : this->MessageHandler<RenderingIntent>::messages){
			switch(intent.action){
				case(RI_ACTIVE_CAMERA):
					this->SetActiveCamera(intent.game_object);
					break;
				case(RI_RENDER_DRAWABLE):
					this->AddGameObjectToDraw(intent.game_object);
					break;
				case(RI_NONE):
					break;
			}
		}
	}

	void Render::AddGameObjectToDraw(GameObject* game_object){
		// Perform validation and correction if needed before adding the objet
		// to the pool;
		Drawable* drawable = game_object->GetComponent<Drawable>();
		if(!drawable || drawable->vao == 0){
			drawable = this->MakeGameObjectDrawable(game_object);
		}
		if( drawable->vao == 0 ){
			return;
		}
		this->objects_to_render_.push_back(game_object);
	}

	Drawable* Render::MakeGameObjectDrawable(GameObject* game_object){
		Drawable* drawable = new Drawable(game_object);
	}

	void Render::SetActiveCamera(GameObject* camera){
		// Should notify the old camera that it's not active anymore maybe?
		this->camera_ = camera;
	}

	GLFWwindow* Render::GetWindow(){
		return this->window_;
	}

	void Render::GLFWErrorCallback(int error, const char* description){
		LOG(ERROR) << "A GLFW error occured : " << error << ":" << description << std::endl;
	}
}
