#include "drawable.hpp"

namespace game{

	Drawable::Drawable() : Drawable((GameObject*)nullptr){

	}

	Drawable::Drawable(GameObject* p) : Component(p){
		this->vao = 0;
		this->shader = 0;
		this->draw_type = 0;
		this->vertex_amount = 0;
		this->offset = 0;
	}

	Drawable::Drawable(Drawable* drawable){
		this->vao = drawable->vao;
		this->shader = drawable->shader;
		this->draw_type = drawable->draw_type;
		this->vertex_amount = drawable->vertex_amount;
		this->offset = drawable->offset;
		this->parent = nullptr;
		this->is_attached = false;
	}

	Drawable* Drawable::Clone(){
		return new Drawable(this);
	}
}
