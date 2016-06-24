#include "entity_builder.hpp"
#include <algorithm>

namespace game{

	EntityBuilder::EntityBuilder(){
		last_generated_id_ = 0;
	}

	EntityBuilder::~EntityBuilder(){

	}

	// Create entity with a new uid, or reuse one from deleted entities
	Entity EntityBuilder::Create(){
		Entity new_entity;
		if(this->unused_id_list_.empty()){
			new_entity.uid = ++last_generated_id_;
		} else {
			new_entity.uid = unused_id_list_[0];
			this->unused_id_list_.erase(unused_id_list_.begin());
		}
		return new_entity;
	}

	//Store deleted entity uid for later reuse
	void EntityBuilder::NotifyDeletionOf(Entity entity){
		if(std::find(unused_id_list_.begin(), unused_id_list_.end(), entity.uid) == unused_id_list_.end()){
			this->unused_id_list_.push_back(entity.uid);
		}
	}
}
