#include "node.hpp"
#include "ecs/ecs.hpp"
#include "common/logger.hpp"
#include "signature_validator.hpp"

namespace game{

	template<class... Components>
	std::vector<Entity> Node<Components...>::GetEntityList(){
		return entities_;
	}

	template<class... Components>
	void Node<Components...>::UpdateListWith(Entity e){
		if(SignatureValidator::Validate<Components...>(e)){
			entities_.push_back(e); // Replace with a function that check if the entity is already in the list or not
		}
	}

	template<class... Components>
	void Node<Components...>::DeleteEntityFromList(Entity entity_to_remove){
		auto it = entities_.begin();
		do{
			if(it->uid == entity_to_remove.uid){
				entities_.erase(it);
				return;
			}
			it++;
		}while(it != entities_.end());
	}

	template<class... Components>
	std::vector<Entity> Node<Components...>::entities_;
}
