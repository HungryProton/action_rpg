#include "node.hpp"

namespace game{

	template<class... Components>
	std::vector<Entity> Node<Components...>::GetEntityList(){
		return entities_;
	}

	template<class... Components>
	void Node<Components...>::UpdateListWith(Entity){

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
