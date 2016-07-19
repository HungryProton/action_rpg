#include "signature_validator.hpp"
#include "ecs/ecs.hpp"

namespace game{

	template<class T>
	bool SignatureValidator::ValidateHelper(Entity e){
		return ecs::GetComponentFromEntity<T>(e) != nullptr;
	}

	template<class T, class T2, class... Components>
	bool SignatureValidator::ValidateHelper(Entity e){
		if(ecs::GetComponentFromEntity<T>(e) == nullptr){ return false; }
		return ValidateHelper<T2, Components...>(e);
	}

	template<class... Components>
	bool SignatureValidator::Validate(Entity e){
		return ValidateHelper<Components...>(e);
	}

}
