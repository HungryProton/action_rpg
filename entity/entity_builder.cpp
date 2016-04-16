#include "entity_builder.hpp"

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
		unsigned long id = this->unused_id_list_.front();
		this->unused_id_list_.pop();
		return id;
	}

	void EntityBuilder::NotifyDelete(unsigned long id){
		this->unused_id_list_.push(id);
	}
}
