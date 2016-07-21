#include "shader_controller.hpp"
#include "common/opengl.hpp"
#include "service/service.hpp"
#include "service/geometry_helper.hpp"
#include "shader/gbuffer.hpp"
#include "shader/deferred_lighting.hpp"

namespace game{

	ShaderController::ShaderController(){
		current_program_ = 0;
	}

	ShaderController::~ShaderController(){
		delete screen_quad_;
	}

	void ShaderController::Initialize(int w, int h){
		width_ = w;
		height_ = h;

		screen_quad_ = new Drawable();
		Service::Get<GeometryHelper>()->MakeDrawableUseScreenSpaceBox(screen_quad_);

		GBuffer* g_buffer = new GBuffer(width_, height_);
		DeferredLighting* d_lighting = new DeferredLighting(width_, height_);

		shaders_.insert(std::make_pair(Program::G_BUFFER, g_buffer));
		shaders_.insert(std::make_pair(Program::LIGHTING, d_lighting));
	}

	void ShaderController::Enable(Program program){
		auto it = shaders_.find(program);
		if(it == shaders_.end()){ return; }

		current_program_ = it->second->GetProgram();
		it->second->Bind();
	}

	GLuint ShaderController::GetUniformLocation(std::string uniform_name){
		return glGetUniformLocation(current_program_, uniform_name.c_str());
	}

	void ShaderController::UniformMatrix4fv(std::string name, glm::mat4 matrix){
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderController::Uniform2f(std::string uname, float x, float y){
		glUniform2f(GetUniformLocation(uname), x, y);
	}

	void ShaderController::RenderToScreen(){
		glBindVertexArray(screen_quad_->vao);
		glDrawElements(screen_quad_->draw_type, screen_quad_->vertex_amount,
								GL_UNSIGNED_INT, BUFFER_OFFSET(screen_quad_->offset));
	}
}
