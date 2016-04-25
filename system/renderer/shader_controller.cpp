#include "shader_controller.hpp"
#include "common/opengl.hpp"
#include "service/service.hpp"
#include "service/geometry_helper.hpp"

namespace game{

	ShaderController::ShaderController(){

	}

	ShaderController::~ShaderController(){
		delete screen_quad_;
	}

	void ShaderController::Initialize(){
		screen_quad_ = new Drawable();
		Service::Get<GeometryHelper>()->MakeDrawableUseScreenSpaceBox(screen_quad_);
	}

	void ShaderController::Enable(Program program){
		switch(program){

			default:
				return;
		}
	}

	void ShaderController::RenderToScreen(){
		glBindVertexArray(screen_quad_->vao);
		glDrawElements(screen_quad_->draw_type, screen_quad_->vertex_amount,
								GL_UNSIGNED_INT, BUFFER_OFFSET(screen_quad_->offset));
	}
}
