#include "constraint_solver.hpp"
#include "component/constraint.hpp"
#include "common/time.hpp"

namespace game{

	ConstraintSolver::ConstraintSolver() : System(){
		Require<Constraint>();
	}

	ConstraintSolver::~ConstraintSolver(){}

	void ConstraintSolver::OnUpdate(Entity e){
		std::vector<Constraint*> constraints = ecs::GetAllComponents<Constraint>(e);

		for(Constraint* c : constraints){
			switch(c->type){
				case(ConstraintType::COPY):
					SolveCopy(c);
					break;
				case(ConstraintType::LOWER_THAN):
					SolveLowerThan(c);
					break;
				case(ConstraintType::GREATER_THAN):
					SolveGreaterThan(c);
					break;
				case(ConstraintType::KEEP_OFFSET):
					SolveKeepOffset(c);
					break;
				case(ConstraintType::NONE):
				default:
					return;
			}
		}
	}

	void ConstraintSolver::SolveCopy(Constraint* c){
		if(!c->soft_resolve){
			*(c->value) = *(c->target_value);
			return;
		}

		glm::vec3 diff = *(c->target_value) - *(c->value);
		if(dot(diff, diff) <= 0.01*c->coefficient*Time::GetPreviousDeltaTime()){
			*(c->value) = *(c->target_value);
			return;
		}

		*(c->value) += diff*c->coefficient*Time::GetPreviousDeltaTime();
	}

	void ConstraintSolver::SolveLowerThan(Constraint*){

	}

	void ConstraintSolver::SolveGreaterThan(Constraint*){

	}

	void ConstraintSolver::SolveKeepOffset(Constraint* c){
		if(!c->soft_resolve){
			*(c->value) = *(c->target_value) + c->offset;
			return;
		}

		glm::vec3 diff = *(c->target_value) + c->offset - *(c->value);
		if(dot(diff, diff) <= c->coefficient*Time::GetPreviousDeltaTime()){
			*(c->value) = *(c->target_value) + c->offset;
			return;
		}

		*(c->value) += diff*c->coefficient*Time::GetPreviousDeltaTime();
	}
}
