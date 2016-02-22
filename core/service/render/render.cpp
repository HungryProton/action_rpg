#include <iostream>
#include "render.hpp"
#include "tools/logger.hpp"
#include "tools/opengl.hpp"
#include "tools/random.hpp"
#include "tools/math.hpp"
#include "core/game/game.hpp"
#include "core/service/helper/geometry_helper.hpp"
#include "core/service/helper/shader_helper.hpp"

#include "core/component/transform.hpp"
#include "core/component/camera.hpp"
#include "core/component/drawable.hpp"
#include "core/component/texture.hpp"
#include "core/component/animated_texture.hpp"

#define KERNEL_SIZE 0.f

namespace game{

	Render::Render(){
		Game::RequestForService<GeometryHelper>();
		Game::RequestForService<ShaderHelper>();
		this->window_ = nullptr;
		this->camera_ = nullptr;
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
		glfwSetErrorCallback(Render::GLFWErrorCallback);
		if(!glfwInit()){
			LOG(ERROR) << "GLFW initialization failed" << std::endl;
			Game::Stop();
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		this->window_ = glfwCreateWindow(1440, 900, "Game", NULL, NULL);
		glfwMakeContextCurrent(this->window_);
		glfwSwapInterval(0);
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
		this->InitializeShaders();
		this->InitializeGBuffer();
		this->InitializeSSAO();

		this->quad_ = new Drawable();
		Locator::Get<GeometryHelper>()->GetScreenSpaceBox(this->quad_);
	}

	void Render::InitializeShaders(){
		ShaderHelper* shaders = Locator::Get<ShaderHelper>();
		this->geometry_pass_shader_ = shaders->GetShader("shader/g_buffer.vs", "shader/g_buffer.frag");
		this->lighting_pass_shader_ = shaders->GetShader("shader/deferred_shading.vs", "shader/deferred_shading.frag");
		this->ssao_shader_ = shaders->GetShader("shader/ssao.vs", "shader/ssao.frag");
		this->ssao_blur_shader_ = shaders->GetShader("shader/ssao_blur.vs", "shader/ssao_blur.frag");

		glUseProgram(this->lighting_pass_shader_);
		glUniform1i( glGetUniformLocation(this->lighting_pass_shader_, "gPositionDepth"), 0);
		glUniform1i( glGetUniformLocation(this->lighting_pass_shader_, "gNormal"), 1);
		glUniform1i( glGetUniformLocation(this->lighting_pass_shader_, "gAlbedoSpec"), 2);
		glUniform1i( glGetUniformLocation(this->lighting_pass_shader_, "ssao"), 3);

		glUseProgram(this->ssao_shader_);
		glUniform1i(glGetUniformLocation(this->ssao_shader_, "gPositionDepth"), 0);
		glUniform1i(glGetUniformLocation(this->ssao_shader_, "gNormal"), 1);
		glUniform1i(glGetUniformLocation(this->ssao_shader_, "texNoise"), 2);
		glUniform1i(glGetUniformLocation(this->ssao_shader_, "samples"), 3);

		glUseProgram(this->ssao_blur_shader_);
		glUniform1i(glGetUniformLocation(this->ssao_shader_, "ssaoInput"), 0);

		glUseProgram(0);
	}

	void Render::InitializeSSAO(){

		// generate hemi sphere kernel
		std::vector<glm::vec3> ssao_kernel;
		for(GLuint i = 0; i < KERNEL_SIZE; i++){
			glm::vec3 sample(
					Random::NextFloat() * 2.f - 1.f,
					Random::NextFloat() * 2.f - 1.f,
					Random::NextFloat()
					);
			sample = glm::normalize(sample);
			sample *= Random::NextFloat();

			GLfloat scale = GLfloat(i) / KERNEL_SIZE;
			scale = Math::lerp(0.1f, 1.0f, scale * scale);
			sample *= scale;
			ssao_kernel.push_back(sample);
		}

		// Save kernel in a 1D texture
		glGenTextures(1, &(this->ssao_kernel_));
		glBindTexture(GL_TEXTURE_2D, this->ssao_kernel_);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB16F, KERNEL_SIZE, 0, GL_RGB, GL_FLOAT,
		&ssao_kernel[0]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Generate noise
		std::vector<glm::vec3> ssao_noise;
		for(GLuint i = 0; i < KERNEL_SIZE; i++){
			glm::vec3 noise(
					Random::NextFloat() * 2.f - 1.f,
					Random::NextFloat() * 2.f - 1.f,
					0.f);
			ssao_noise.push_back(noise);
		}

		// Save noise in texture
		glGenTextures(1, &(this->noise_texture_));
		glBindTexture(GL_TEXTURE_2D, this->noise_texture_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT,
		&ssao_noise[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Generate framebuffer
		int width, height;
		glfwGetWindowSize(this->window_, &width, &height);

		glGenFramebuffers(1, &(this->ssao_buffer_));
		glBindFramebuffer(GL_FRAMEBUFFER, this->ssao_buffer_);

		glGenTextures(1, &(this->ssao_color_buffer_));
		glBindTexture(GL_TEXTURE_2D, this->ssao_color_buffer_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RGB,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		this->ssao_color_buffer_, 0);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG(CRITICAL) << "SSAO Framebuffer not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Generate blur buffer
		glGenFramebuffers(1, &(this->ssao_blur_buffer_));
		glBindFramebuffer(GL_FRAMEBUFFER, this->ssao_blur_buffer_);
    glGenTextures(1, &(this->ssao_blur_color_buffer_));
    glBindTexture(GL_TEXTURE_2D, this->ssao_blur_color_buffer_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->ssao_blur_color_buffer_, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOG(CRITICAL) << "SSAO Blur Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

	void Render::InitializeGBuffer(){

		int width, height;
		glfwGetWindowSize(this->window_, &width, &height);

		glGenFramebuffers(1, &(this->g_buffer_));
		glBindFramebuffer(GL_FRAMEBUFFER, this->g_buffer_);

		// Position buffer
		glGenTextures(1, &(this->g_position_depth_));
		glBindTexture(GL_TEXTURE_2D, this->g_position_depth_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		this->g_position_depth_, 0);

		// - Normal color buffer
		glGenTextures(1, &(this->g_normal_));
		glBindTexture(GL_TEXTURE_2D, this->g_normal_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
		this->g_normal_, 0);

		// - Color + Specular color buffer
		glGenTextures(1, &(this->g_albedo_spec_));
		glBindTexture(GL_TEXTURE_2D, this->g_albedo_spec_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
		this->g_albedo_spec_, 0);

		// - Tell OpenGL which color attachments we’ll use (of this framebuffer)
		// for rendering
		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
	 	GL_COLOR_ATTACHMENT2};
		glDrawBuffers(3, attachments);

		// Create and attach depth buffer
    glGenRenderbuffers(1, &(this->depth_buffer_));
    glBindRenderbuffer(GL_RENDERBUFFER, this->depth_buffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depth_buffer_);

    // - Finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOG(ERROR) << "Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Render::UpdateCamera(){
		Transform* transform = this->camera_->parent->GetComponent<Transform>();
		this->camera_->view = glm::lookAt(transform->position,
																 this->camera_->target,
																 this->camera_->up);
	}

	void Render::RenderDrawingPool(){
		glfwSwapBuffers(this->window_);

		// Geometry pass
		glBindFramebuffer(GL_FRAMEBUFFER, this->g_buffer_);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glm::mat4 view = this->camera_->view;
			glm::mat4 projection = this->camera_->projection;
			glm::mat4 model;
			glUseProgram(this->geometry_pass_shader_);
			GLuint view_id = glGetUniformLocation(this->geometry_pass_shader_, "View");
			GLuint projection_id = glGetUniformLocation(this->geometry_pass_shader_, "Projection");
			glUniformMatrix4fv(view_id, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projection_id, 1, GL_FALSE, glm::value_ptr(projection));

			for(GameObject* game_object : this->objects_to_render_){
				Drawable* drawable = game_object->GetComponent<Drawable>();
				Transform* transform = game_object->GetComponent<Transform>();
				Texture* texture = game_object->GetComponent<Texture>();
				AnimatedTexture* animated_texture = game_object->GetComponent<AnimatedTexture>();
				Mesh* mesh = game_object->GetComponent<Mesh>();

				// Set every texture to the same scale
				// Kind of an ugly hack, find a more elegant way to do it
				glm::vec3 local_scale = glm::vec3(1.f, 1.f, 1.f);
				if(!mesh){
					if(texture){ local_scale = texture->local_scale; }
					if(animated_texture){ local_scale = animated_texture->local_scale; }
				}

				model = this->GetModelMatrixFor(transform, local_scale);
				GLuint model_id = glGetUniformLocation(this->geometry_pass_shader_, "Model");
				glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(model));

				//-- Draw section
				glBindVertexArray(drawable->vao);

				// Update uniforms in case of animated textures
				GLuint tex_ratio = glGetUniformLocation(this->geometry_pass_shader_, "TexRatio");
				GLuint tex_shift = glGetUniformLocation(this->geometry_pass_shader_, "TexShift");
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

				glDrawElements(drawable->draw_type, drawable->vertex_amount,
						GL_UNSIGNED_INT, BUFFER_OFFSET(drawable->offset));
			}

		glBindFramebuffer(GL_FRAMEBUFFER, this->ssao_buffer_);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(this->ssao_shader_);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->g_position_depth_);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, this->g_normal_);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, this->noise_texture_);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_1D, this->ssao_kernel_);

			projection_id = glGetUniformLocation(this->ssao_shader_, "projection");
			glUniformMatrix4fv(projection_id, 1, GL_FALSE, glm::value_ptr(this->camera_->projection));
			GLuint kernel_size_id = glGetUniformLocation(this->ssao_shader_, "kernelSize");
			glUniform1i(kernel_size_id, KERNEL_SIZE);
			this->RenderQuad();

		// 3. Blur SSAO texture to remove noise
		glBindFramebuffer(GL_FRAMEBUFFER, this->ssao_blur_buffer_);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(this->ssao_blur_shader_);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->ssao_color_buffer_);
			RenderQuad();

		// 4. Lighting Pass
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(this->lighting_pass_shader_);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->g_position_depth_);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, this->g_normal_);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, this->g_albedo_spec_);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, this->ssao_blur_color_buffer_);
			this->RenderQuad();

		this->ClearDrawingPool();
	}

	void Render::RenderQuad(){
		glBindVertexArray(this->quad_->vao);
		glDrawElements(this->quad_->draw_type, this->quad_->vertex_amount,
				GL_UNSIGNED_INT, BUFFER_OFFSET(this->quad_->offset));
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

	glm::mat4 Render::GetModelMatrixFor(Transform* transform, glm::vec3 local_scale){

		glm::mat4 translation = glm::translate(glm::mat4(1.0f),
																					 glm::vec3(transform->position));

		glm::mat4 rotation_x = glm::rotate(translation, transform->rotation.x,
																			 glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 rotation_xy = glm::rotate(rotation_x, transform->rotation.y,
																				glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 rotation_xyz = glm::rotate(rotation_xy, transform->rotation.z,
																				glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 scale = glm::scale(transform->scale * local_scale);

		return rotation_xyz * scale;
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
