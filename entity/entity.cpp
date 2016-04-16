#include "entity.hpp"

namespace game{

	unsigned long Entity::Create(){
		return builder.Create();
	}

	void Entity::Destroy(unsigned long id){
		builder.NotifyDelete(id);
	}

	EntityBuilder Entity::builder;
}
