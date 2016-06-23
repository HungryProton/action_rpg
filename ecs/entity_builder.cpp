#include "entity_builder.hpp"
#include <algorithm>

namespace game{

	EntityBuilder::EntityBuilder(){
		last_generated_id_ = 0;
	}

	EntityBuilder::~EntityBuilder(){

	}

	Entity EntityBuilder::Create(){
		if(this->unused_id_list_.empty()){
			return ++last_generated_id_;
		}
		Entity id = unused_id_list_[0];
		this->unused_id_list_.erase(unused_id_list_.begin());
		return id;
	}

	void EntityBuilder::NotifyDelete(Entity id){
		if(std::find(unused_id_list_.begin(), unused_id_list_.end(), id) == unused_id_list_.end()){
			this->unused_id_list_.push_back(id);
		}
	}
}
