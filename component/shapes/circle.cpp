#include <iostream>
#include "circle.hpp"
#include "entity/entity.hpp"

namespace game{

	Circle::Circle() : ShapeComponent(){
		this->radius = 1.f;
		this->vertex_amount = 10;
	}

	Circle::Circle(unsigned long id): Circle(){
		Entity::AttachComponent<Circle>(id, this);
	}

	Circle::Circle(float radius, unsigned long p) : Circle(p){
		this->radius = radius;
	}

	Circle::Circle(float radius, int res, unsigned long p) : Circle(radius, p){
		this->vertex_amount = res;
	}

	Circle::Circle(Circle* circle) : Circle(){
		this->radius = circle->radius;
		this->vertex_amount = circle->vertex_amount;
	}

	Circle* Circle::Clone(){
		return new Circle(this);
	}
}

