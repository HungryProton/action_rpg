#include <iostream>
#include "render.hpp"
#include "tools/logger.hpp"
#include "tools/opengl.hpp"
#include "core/game/game.hpp"
#include "core/service/helper/geometry_helper.hpp"
#include "core/service/helper/shader_helper.hpp"

#include "core/component/transform.hpp"
#include "core/component/camera.hpp"
#include "core/component/drawable.hpp"
#include "core/component/texture.hpp"
#include "core/component/animated_texture.hpp"

namespace game{

	Render::Render(){
		Game::RequestForService<GeometryHelper>();
		Game::RequestForService<ShaderHelper>();
		this->window_ = nullptr;
		this->camera_ = nullptr;
		this->InitializeGLFW();
		this->InitializeOpenGL();
		this->shader_ = Locator::Get<ShaderHelper>()->GetShader("shader/vertex.c",
																									"shader/fragment.c");
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
		LOG(INFO) << "GLFW initialized" << std::endl;
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
		glClearColor(0.67, 0.84, 0.90, 1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Render::Update(){
		ProcessReceivedMessages();
		UpdateCamera();
		RenderDrawingPool();

	}

	void Render::ProcessReceivedMessages(){
		for(RenderingIntent intent : this->MessageHandler<RenderingIntent>::messages_){
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

		this->MessageHandler<RenderingIntent>::messages_.clear();
	}

	void Render::UpdateCamera(){
		Transform* transform = this->camera_->parent->GetComponent<Transform>();
		glm::mat4 view = glm::lookAt(transform->position,
																 this->camera_->target,
																 this->camera_->up);
		this->camera_->view_projection = this->camera_->projection * view;
	}

	void Render::RenderDrawingPool(){
		glfwSwapBuffers(this->window_);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for(GameObject* game_object : this->objects_to_render_){
			Drawable* drawable = game_object->GetComponent<Drawable>();
			Transform* transform = game_object->GetComponent<Transform>();
			Texture* texture = game_object->GetComponent<Texture>();
			AnimatedTexture* animated_texture = game_object->GetComponent<AnimatedTexture>();

			glm::mat4 model_view_projection = GetModelViewProjectionMatrixFor(transform);

			check_gl_error();
			glBindVertexArray(drawable->vao);

			check_gl_error();
				glUseProgram(this->shader_);

			check_gl_error();
					GLuint matrix_id = glGetUniformLocation(this->shader_, "MVP");
					glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &model_view_projection[0][0]);

					GLuint tex_ratio = glGetUniformLocation(this->shader_, "TexRatio");
					GLuint tex_shift = glGetUniformLocation(this->shader_, "TexShift");
					glUniform2f(tex_ratio, -1, -1);

					if(texture){
						texture->Bind(GL_TEXTURE0);
					}else if(animated_texture){
						animated_texture->Bind(GL_TEXTURE0);
						glUniform2f(tex_ratio, animated_texture->current_ratio.x, animated_texture->current_ratio.y);
						glUniform2f(tex_shift, animated_texture->shift.x, animated_texture->shift.y);
					} else {
						glBindTexture( GL_TEXTURE_2D, 0);
					}

			check_gl_error();
					glEnable(GL_BLEND);

			check_gl_error();
						glDrawElements(drawable->draw_type, drawable->vertex_amount,
								GL_UNSIGNED_INT, BUFFER_OFFSET(drawable->offset));
			check_gl_error();

		}

		this->ClearDrawingPool();
	}

	void Render::AddGameObjectToDraw(GameObject* game_object){
		// Perform validation and correction if needed before adding the objet
		// to the pool;
		Drawable* drawable = game_object->GetComponent<Drawable>();
		if(!drawable){
			return;
		}
		if( drawable->vao == 0 ){
			drawable = this->MakeGameObjectDrawable(game_object);
			if(!drawable || drawable->vao == 0){ return; }
		}
		this->objects_to_render_.push_back(game_object);
	}

	void Render::ClearDrawingPool(){
		this->objects_to_render_.clear();
	}

	Drawable* Render::MakeGameObjectDrawable(GameObject* game_object){
		Drawable* drawable = game_object->GetComponent<Drawable>();
		if(drawable == nullptr){
			return nullptr;
		}

		GeometryHelper* geometry_helper = Locator::Get<GeometryHelper>();
		Mesh* mesh = game_object->GetComponent<Mesh>();
		Texture* texture = game_object->GetComponent<Texture>();
		AnimatedTexture* animated_texture = game_object->GetComponent<AnimatedTexture>();
		if(mesh){
			geometry_helper->GetMesh(mesh, drawable);
		} else if (texture || animated_texture){
			geometry_helper->GetBox(drawable);
		} else {
			LOG(DEBUG) << "No graphic component is attached to the gameobject" << std::endl;
		}
		return drawable;
	}

	glm::mat4 Render::GetModelViewProjectionMatrixFor(Transform* transform){
		glm::mat4 translation = glm::translate(glm::mat4(1.0f),
																					 glm::vec3(transform->position));

		glm::mat4 rotation_x = glm::rotate(translation, transform->rotation.x,
																			 glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 rotation_xy = glm::rotate(rotation_x, transform->rotation.y,
																				glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 rotation_xyz = glm::rotate(rotation_xy, transform->rotation.z,
																				glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 scale = glm::scale(transform->scale);

		glm::mat4 model = rotation_xyz * scale;

		return this->camera_->view_projection * model;
	}

	void Render::SetActiveCamera(GameObject* camera){
		// Should notify the old camera that it's not active anymore maybe?
		LOG(INFO) << "Setting the new camera" << std::endl;
		this->camera_ = camera->GetComponent<Camera>();
	}

	GLFWwindow* Render::GetWindow(){
		return this->window_;
	}

	void Render::GLFWErrorCallback(int error, const char* description){
		LOG(ERROR) << "A GLFW error occured : " << error << ":" << description << std::endl;
	}
}
