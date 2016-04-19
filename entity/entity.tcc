#include "entity.hpp"
#include "component_register.hpp"

namespace game{

	template<class T>
	T* Entity::GetComponent(unsigned long id){
		return ComponentRegister<T>::GetComponent(id);
	}

	template<class T>
	void Entity::AttachComponent(unsigned long id, T* component){
		ComponentRegister<T>::AttachComponent(id, component);
		auto pair = delete_map_.find(id);
		if(pair == delete_map_.end()){
			std::vector<void(*)(unsigned long)> functions;
			functions.push_back(ComponentRegister<T>::RemoveComponent);
			delete_map_.insert(std::make_pair(id, functions));
		} else {
			pair->second.push_back(ComponentRegister<T>::RemoveComponent);
		}
	}
}
