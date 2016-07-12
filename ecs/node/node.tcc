#include "node.hpp"

namespace game{

	template<class... Types>
	Node<Types...>::Node(){ }

	template<class... Types>
	Node<Types...>::~Node(){ }

	template<class... Types>
	std::vector<Entity> Node<Types...>::GetEntityList(){
		return entities_;
	}

	template<class... Types>
	void Node<Types...>::UpdateListWith(Entity){

	}

	template<class... Types>
	void Node<Types...>::DeleteEntityFromList(Entity entity_to_remove){
		auto it = entities_.begin();
		do{
			if(it->uid == entity_to_remove.uid){
				entities_.erase(it);
				return;
			}
			it++;
		}while(it != entities_.end());
	}
}
