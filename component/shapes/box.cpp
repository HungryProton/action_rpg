#include <glm/glm.hpp>
#include "box.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	Box::Box(){
		this->width = -1;
		this->height = -1;
	}

	Box::Box(float w, float h){
		this->SetDimensions(w,h);
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
