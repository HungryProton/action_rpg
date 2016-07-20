#include "node.hpp"
#include "ecs/ecs.hpp"
#include "common/logger.hpp"
#include "signature_validator.hpp"

namespace game{

	template<class... Components>
	bool Node<Components...>::IsEntityInList(Entity e){
		for(auto entity : entities_){
			if(e.uid == entity.uid){ return true; }
		}
		return false;
	}

	template<class... Components>
	void Node<Components...>::InsertEntity(Entity e){
		if(IsEntityInList(e)){ return; }
		entities_.push_back(e);
	}

	template<class... Components>
	std::vector<Entity> Node<Components...>::GetEntityList(){
		return entities_;
	}

	template<class... Components>
	void Node<Components...>::UpdateListWith(Entity e){
		if(SignatureValidator::Validate<Components...>(e)){
			InsertEntity(e);
		} else {
			DeleteEntityFromList(e);
		}
	}

	template<class... Components>
	void Node<Components...>::DeleteEntityFromList(Entity entity_to_remove){
		auto it = entities_.begin();
		while(it != entities_.end()){
			if(it->uid == entity_to_remove.uid){
				entities_.erase(it);
				return;
			}
			it++;
		}
	}

	template<class... Components>
	void Node<Components...>::ClearMemory(){
		entities_.clear();
	}

	template<class... Components>
	std::vector<Entity> Node<Components...>::entities_;
}
