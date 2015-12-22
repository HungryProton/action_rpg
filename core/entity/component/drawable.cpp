#include "drawable.hpp"

namespace game{

	Drawable::Drawable() : Drawable(nullptr){

	}

	Drawable::Drawable(GameObject* p) : Component(p){
		this->vao = 0;
		this->shader = 0;
		this->draw_type = 0;
		this->vertex_amount = 0;
		this->offset = 0;
	}
}
