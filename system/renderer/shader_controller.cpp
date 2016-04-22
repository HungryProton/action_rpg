#include "shader_controller.hpp"
#include "common/opengl.hpp"

namespace game{

	ShaderController::ShaderController(){

	}

	ShaderController::~ShaderController(){

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
