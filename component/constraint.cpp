#include "constraint.hpp"
#include "common/logger.hpp"

namespace game{

	Constraint::Constraint(){
		type = ConstraintType::NONE;
		value = nullptr;
		target_value = nullptr;
		soft_resolve = false;
		coefficient = 0.5f;
		name = "";
	}

	void Constraint::SetOffset(glm::vec3* val, glm::vec3* target){
		type = ConstraintType::KEEP_OFFSET;
		offset = *val - *target;
		target_value = target;
		value = val;
	}
}
