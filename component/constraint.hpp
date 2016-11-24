#ifndef GAME_COMPONENT_CONSTRAINT_HPP_
#define GAME_COMPONENT_CONSTRAINT_HPP_

#include "common/glm.hpp"

namespace game{

	enum class ConstraintType{
		NONE,
		COPY,
		LOWER_THAN,
		GREATER_THAN,
		KEEP_OFFSET
	};

	// Should probably be a templated class
	struct Constraint{
		ConstraintType type;
		bool soft_resolve;	// Whether the constraint applies immediately or by soft progressive increments
		float coefficient; // the increment's value if soft is true;

		glm::vec3* target_value;
		glm::vec3* value;
		glm::vec3 offset;

		Constraint();
		void SetOffset(glm::vec3* value, glm::vec3* target_value);
	};
}

#endif //GAME_COMPONENT_CONSTRAINT_HPP_
