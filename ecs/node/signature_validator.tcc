#include "signature_validator.hpp"
#include "ecs/ecs.hpp"

namespace game{

	// Check if the given entity has at least one component of type T
	template<class T>
	bool SignatureValidator::ValidateHelper(Entity e){
		return !ecs::GetAllComponents<T>(e).empty();
	}

	template<class T, class T2, class... Components>
	bool SignatureValidator::ValidateHelper(Entity e){
		if(!ValidateHelper<T>(e)){ return false; }
		return ValidateHelper<T2, Components...>(e);
	}

	template<class... Components>
	bool SignatureValidator::Validate(Entity e){
		return ValidateHelper<Components...>(e);
	}

}
