#include <iostream>
#include "circle.hpp"
#include "core/entity/game_object.hpp"

namespace game{

	Circle::Circle(): Component(){
		this->radius = 1.f;
		this->vertex_amount = 10;
	}

	Circle::Circle(GameObject* p): Circle(){
		if(p){
			p->AttachComponent(this);
		}
	}

	Circle::Circle(float radius, GameObject* p) : Circle(p){
		this->radius = radius;
	}

	Circle::Circle(float radius, int res, GameObject* p) : Circle(p){
		this->radius = radius;
		this->vertex_amount = res;
	}
}

