#include "entity.hpp"

namespace game{

	unsigned long Entity::Create(){
		return builder_.Create();
	}

	void Entity::Destroy(unsigned long id){
		builder_.NotifyDelete(id);
		auto pair = delete_map_.find(id);
		if(pair == delete_map_.end()){ return; }

		for(auto delete_function : pair->second){
			delete_function(id);
		}
		delete_map_.erase(pair);
	}

	EntityBuilder Entity::builder_;
	std::map<unsigned long, std::vector<void(*)(unsigned long)>> Entity::delete_map_;
}
