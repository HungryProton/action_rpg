#include "ecs.hpp"
#include "system/system_register.hpp"
#include "common/logger.hpp"

namespace game{

	Entity ecs::CreateEntity(){
		return entity_builder_.Create();
	}

	void ecs::DestroyEntity(Entity e){
		NotifyEntityWasDeleted(e);
		entity_builder_.NotifyDeletionOf(e);
		for(auto delete_fcn : component_registers_delete_fcn_){
			delete_fcn(e);
		}
	}

	void ecs::NotifyEntityHasChanged(Entity e){
		for(auto update_fcn : node_update_fcn_){
			update_fcn(e);
		}
	}

	void ecs::NotifyEntityWasDeleted(Entity e){
		for(auto delete_fcn : node_delete_fcn_){
			delete_fcn(e);
		}
	}

	void ecs::ClearMemory(){
		for(auto clear_fcn : component_registers_clear_fcn_){
			clear_fcn();
		}
		for(auto clear_fcn : nodes_clear_fcn_){
			clear_fcn();
		}
		node_delete_fcn_.clear();
		node_update_fcn_.clear();
		nodes_clear_fcn_.clear();
		component_registers_clear_fcn_.clear();
	}

	std::vector<void(*)(Entity)> ecs::node_update_fcn_;
	std::vector<void(*)(Entity)> ecs::node_delete_fcn_;
	std::vector<void(*)()> ecs::nodes_clear_fcn_;
	std::vector<void(*)()> ecs::component_registers_clear_fcn_;
	std::vector<void(*)(Entity)> ecs::component_registers_delete_fcn_;
	EntityBuilder ecs::entity_builder_;
}
