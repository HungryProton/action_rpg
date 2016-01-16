#ifndef GAME_CORE_COMPONENT_CONSTRAINT_HPP
#define GAME_CORE_COMPONENT_CONSTRAINT_HPP

#include "tools/opengl.hpp"
#include "component.hpp"

namespace game{

	enum class ConstraintType{
		NONE,
		COPY,
		LOWER_THAN,
		GREATER_THAN,
	};

	struct Constraint : public Component{

		ConstraintType type;
		bool soft_resolve;	// Whether the constraint applies immediately or by soft progressive increments
		float coefficient; // the increment's value if soft is true;

		glm::vec3* target_value;
		glm::vec3* value;

		// Helper
		Constraint();
		Constraint(GameObject*);
		Constraint(Constraint*);
		virtual Constraint* Clone();
		virtual void Update();
		void SolveCopy();
		void SolveLowerThan();
		void SolveGreaterThan();
	};
}
#endif //GAME_CORE_COMPONENT_CONSTRAINT_HPP
