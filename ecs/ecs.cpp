#include "entity.hpp"
#include "system_register.hpp"

namespace game{

	Entity Entity::Create(){
		return builder_.Create();
	}

	void Entity::Destroy(Entity id){
		builder_.NotifyDelete(id);
		SystemRegister::DissociateEntityFromAll(id);

		auto pair = delete_map_.find(id);
		if(pair == delete_map_.end()){ return; }

		for(auto delete_function : pair->second){
			delete_function(id);
		}
		delete_map_.erase(pair);
	}

	Entity Entity::Clone(Entity id){
		unsigned int new_entity = Entity::Create();

		auto pair = clone_map_.find(id);
		if(pair == clone_map_.end()){ return new_entity; }

		for(auto clone_function : pair->second){
			clone_function(id, new_entity);
		}
		SystemRegister::CloneAssociationOfInto(id, new_entity);

		return new_entity;
	}

	void Entity::ClearMemory(){
		Entity id = builder_.Create();

		while(id > 0){
			Destroy(id);
			id--;
		}
	}

	EntityBuilder Entity::builder_;
	std::map<Entity, std::vector<void(*)(Entity)>> Entity::delete_map_;
	std::map<Entity, std::vector<void(*)(Entity, Entity)>> Entity::clone_map_;
}
