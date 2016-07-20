#include <iostream>
#include "circle.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	Circle::Circle() : ShapeComponent(){
		this->radius = 1.f;
		this->vertex_amount = 10;
	}

	Circle::Circle(float radius){
		this->radius = radius;
	}

	Circle::Circle(float radius, int res) : Circle(radius){
		this->vertex_amount = res;
	}
}

