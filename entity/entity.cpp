#include "entity.hpp"
#include "system_register.hpp"

namespace game{

	unsigned long Entity::Create(){
		return builder_.Create();
	}

	void Entity::Destroy(unsigned long id){
		builder_.NotifyDelete(id);
		SystemRegister::DissociateEntityFromAll(id);

		auto pair = delete_map_.find(id);
		if(pair == delete_map_.end()){ return; }

		for(auto delete_function : pair->second){
			delete_function(id);
		}
		delete_map_.erase(pair);
	}

	unsigned long Entity::Clone(unsigned long id){
		unsigned int new_entity = Entity::Create();

		return new_entity;
	}

	void Entity::ClearMemory(){
		unsigned long id = builder_.Create();

		while(id > 0){
			Destroy(id);
			id--;
		}
	}

	EntityBuilder Entity::builder_;
	std::map<unsigned long, std::vector<void(*)(unsigned long)>> Entity::delete_map_;
}
