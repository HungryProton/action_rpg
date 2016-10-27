#include "common.hpp"
#include "transform.hpp"
#include "ecs/ecs.hpp"
#include "common/math.hpp"

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

	Direction GetDirectionFromVector(glm::vec3 dir){
		float angle = atan2(dir.y, dir.x) * 180 / PI;

		if((angle > -180 && angle < -157.5) || (angle < 180 && angle > 157.5)){
			return Direction::W;
		} else if (angle > -157.5 && angle < -112.5){
			return Direction::NW;
		} else if (angle > -112.5 && angle < -67.5){
			return Direction::N;
		} else if (angle > -67.5 && angle < -22.5){
			return Direction::NE;
		} else if (angle > -22.5 && angle < 22.5){
			return Direction::E;
		} else if (angle > 22.5 && angle < 67.5){
			return Direction::SE;
		} else if (angle > 67.5 && angle < 112.5){
			return Direction::S;
		} else if (angle > 112.5 && angle < 157.5){
			return Direction::SW;
		}
		return Direction::LAST;
	}
}

