#include <glm/glm.hpp>
#include "box.hpp"
#include "core/entity/game_object.hpp"

namespace game{

	Box::Box(): Component(){
		this->width = -1;
		this->height = -1;
	}

	Box::Box(GameObject* p):Box(){
		p->AttachComponent(this);
	}

	Box::Box(float w, float h, GameObject* p) : Box(p){
		this->SetDimensions(w,h);
	}

	Box::Box(Box* box) : Box(){
		this->width = box->width;
		this->height = box->height;
	}

	Box* Box::Clone(){
		return new Box(this);
	}

	void Box::SetDimensions(glm::vec2 dim){
		this->width = dim.x;
		this->height = dim.y;
	}

	void Box::SetDimensions(float w, float h){
		this->width = w;
		this->height = h;
	}

}
