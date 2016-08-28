#include "common.hpp"
#include "transform.hpp"
#include "ecs/ecs.hpp"

namespace game{

	bool Area::IsObjectWithin(Entity object){
		Transform* t = ecs::GetComponent<Transform>(object);
		if(!t){return false;}

		switch(this->type){
			case AreaType::RECTANGLE:{
				glm::vec2 half_size = this->size/2.f;
				if(t->position.x > this->position.x + half_size.x){ return false; }
				if(t->position.x < this->position.x - half_size.x){ return false; }
				if(t->position.y > this->position.y + half_size.y){ return false; }
				if(t->position.y < this->position.y - half_size.y){ return false; }
				return true;
			}
			case AreaType::CIRCLE:
				return glm::distance(t->position, this->position) <= (this->radius*2);
			case AreaType::CONE:
			default:
				return false;
		}
	}
}

