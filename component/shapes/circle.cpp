#include <iostream>
#include "circle.hpp"
#include "ecs/entity.hpp"

namespace game{

	Circle::Circle() : ShapeComponent(){
		this->radius = 1.f;
		this->vertex_amount = 10;
	}

	Circle::Circle(Entity id): Circle(){
		Entity::AttachComponent<Circle>(id, this);
	}

	Circle::Circle(float radius, Entity p) : Circle(p){
		this->radius = radius;
	}

	Circle::Circle(float radius, int res, Entity p) : Circle(radius, p){
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

