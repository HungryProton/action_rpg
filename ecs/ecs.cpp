#include "ecs.hpp"

namespace game{

	Entity ecs::CreateEntity(){
		return entity_builder_.Create();
	}

	void ecs::NotifyEntityHasChanged(Entity e){
		for(auto node : nodes_){
			node->UpdateListWith(e);
		}
	}

	void ecs::NotifyEntityWasDeleted(Entity e){
		for(auto node : nodes_){
			node->DeleteEntityFromList(e);
		}
	}

	void ecs::ClearMemory(){
		for(auto clear_fcn : component_registers_clear_fcn_){
			clear_fcn();
		}
	}

	std::vector<BaseNode*> ecs::nodes_;
	std::vector<void(*)()> ecs::component_registers_clear_fcn_;
	EntityBuilder ecs::entity_builder_;
}
