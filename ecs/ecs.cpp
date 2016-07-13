#include "ecs.hpp"
#include "common/logger.hpp"

namespace game{

	Entity ecs::CreateEntity(){
		return entity_builder_.Create();
	}

	void ecs::NotifyEntityHasChanged(Entity e){
		for(auto update_fcn : node_update_fcn_){
			LOG(DEBUG) << "Called update" << std::endl;
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
	}

	std::vector<void(*)(Entity)> ecs::node_update_fcn_;
	std::vector<void(*)(Entity)> ecs::node_delete_fcn_;
	std::vector<void(*)()> ecs::component_registers_clear_fcn_;
	EntityBuilder ecs::entity_builder_;
}
