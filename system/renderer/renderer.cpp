#include "renderer.hpp"
#include "entity/entity.hpp"
#include "component/camera.hpp"

namespace game{

	Renderer::Renderer() : System(){
		context_controller_.Initialize();
		shader_controller_.Initialize();
	}

	Renderer::~Renderer(){

	}

	void Renderer::BeforeUpdate(){
		camera_controller_.Update();
		context_controller_.SwapBuffers();
		shader_controller_.Enable(Program::G_BUFFER);
	}

	void Renderer::OnUpdate(unsigned long entity){
		RenderComponent node = GetComponentsFor(entity);
		if(!node.is_valid){ return; }

		Draw(node.drawable);
	}

	void Renderer::AfterUpdate(){
		shader_controller_.Enable(Program::LIGHTING);
		shader_controller_.RenderToScreen();
	}


	void Renderer::Draw(Drawable* drawable){
		glBindVertexArray(drawable->vao);
		glDrawElements(drawable->draw_type, drawable->vertex_amount,
				GL_UNSIGNED_INT, BUFFER_OFFSET(drawable->offset));
	}

	RenderComponent Renderer::GetComponentsFor(unsigned long entity){
		RenderComponent node;
		node.is_valid = false;
		node.drawable = Entity::GetComponent<Drawable>(entity);

		if(!node.drawable){ return node; }
		if(node.drawable->vao == 0){
			int err = drawable_builder_.UpdateDrawableOf(entity);
			if(err){ return node; }
		}
		node.transform = Entity::GetComponent<Transform>(entity);
		node.texture = Entity::GetComponent<Texture>(entity);
		node.mesh = Entity::GetComponent<Mesh>(entity);
		node.is_valid = true;
		return node;
	}

	GLFWwindow* Renderer::GetWindow(){
		return this->context_controller_.GetWindow();
	}
}
