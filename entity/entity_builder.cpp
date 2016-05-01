#include "entity_builder.hpp"
#include <algorithm>

namespace game{

	EntityBuilder::EntityBuilder(){
		last_generated_id_ = 0;
	}

	EntityBuilder::~EntityBuilder(){

	}

	unsigned long EntityBuilder::Create(){
		if(this->unused_id_list_.empty()){
			return ++last_generated_id_;
		}
		unsigned long id = unused_id_list_[0];
		this->unused_id_list_.erase(unused_id_list_.begin());
		return id;
	}

	void EntityBuilder::NotifyDelete(unsigned long id){
		if(std::find(unused_id_list_.begin(), unused_id_list_.end(), id) == unused_id_list_.end()){
			this->unused_id_list_.push_back(id);
		}
	}
}
