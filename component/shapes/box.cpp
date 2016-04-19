#include <glm/glm.hpp>
#include "box.hpp"
#include "entity/entity.hpp"

namespace game{

	Box::Box() : ShapeComponent(){
		this->width = -1;
		this->height = -1;
	}

	Box::Box(unsigned long id) : Box(){
		Entity::AttachComponent<Box>(id, this);
	}

	Box::Box(float w, float h, unsigned long id) : Box(id){
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
