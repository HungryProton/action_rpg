#include "renderer.hpp"
#include "entity/entity.hpp"

namespace game{

	Renderer::Renderer() : System(){
		context_controller_.Initialize();
	}

	Renderer::~Renderer(){

	}

	void Renderer::BeforeUpdate(){

	}

	void Renderer::OnUpdate(unsigned long){

	}

	RenderComponent* Renderer::GetComponentsFor(unsigned long entity){
		RenderComponent* node;
		node->drawable = Entity::GetComponent<Drawable>(entity);

		if(!node->drawable){ return nullptr; }
		if(node->drawable->vao == 0){
			int err = drawable_builder_.UpdateDrawableOf(entity);
			if(err){ return nullptr; }
		}
		node->transform = Entity::GetComponent<Transform>(entity);
		node->texture = Entity::GetComponent<Texture>(entity);
		node->mesh = Entity::GetComponent<Mesh>(entity);
		return node;
	}

	GLFWwindow* Renderer::GetWindow(){
		return this->context_controller_.GetWindow();
	}
}
