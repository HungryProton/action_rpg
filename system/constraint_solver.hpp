#ifndef GAME_SYSTEM_CONSTRAINT_SOLVER_HPP_
#define GAME_SYSTEM_CONSTRAINT_SOLVER_HPP_

#include "system.hpp"
#include "component/constraint.hpp"

namespace game{

	class ConstraintSolver : public System{
		public:
			ConstraintSolver();
			~ConstraintSolver();

		protected:
			void OnUpdate(Entity);

		private:
			void SolveCopy(Constraint*);
			void SolveLowerThan(Constraint*);
			void SolveGreaterThan(Constraint*);
			void SolveKeepOffset(Constraint*);
	};
}

#endif //GAME_SYSTEM_CONSTRAINT_SOLVER_HPP_
