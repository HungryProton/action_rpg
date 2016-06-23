#include "entity.hpp"
#include "component_register.hpp"

namespace game{

	template<class T>
	T* Entity::GetComponent(unsigned long id){
		return ComponentRegister<T>::GetComponent(id);
	}

	template<class T>
	void Entity::AttachComponent(unsigned long id, T* component){
		if(id == 0){ return; }
		int err = ComponentRegister<T>::AttachComponent(id, component);
		if(err){ return; }

		auto pair = delete_map_.find(id);
		if(pair == delete_map_.end()){
			std::vector<void(*)(unsigned long)> functions;
			functions.push_back(ComponentRegister<T>::RemoveComponent);
			delete_map_.insert(std::make_pair(id, functions));
		} else {
			pair->second.push_back(ComponentRegister<T>::RemoveComponent);
		}

		auto pair2 = clone_map_.find(id);
		if(pair2 == clone_map_.end()){
			std::vector<void(*)(unsigned long, unsigned long)> functions;
			functions.push_back(ComponentRegister<T>::CloneFromTo);
			clone_map_.insert(std::make_pair(id, functions));
		} else {
			pair2->second.push_back(ComponentRegister<T>::CloneFromTo);
		}
	}
}
