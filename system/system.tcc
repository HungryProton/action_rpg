#include "system.hpp"
#include "ecs/ecs.hpp"

namespace game{

	template<class... Components>
	void System::Require(){
		ecs::CreateSignature<Components...>();
		get_matching_entities_ = ecs::GetEntitiesWithComponents<Components...>;
	}
}
