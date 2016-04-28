#include "component_register.hpp"
#include "common/logger.hpp"

namespace game{

	template<class T>
	void ComponentRegister<T>::AttachComponent(unsigned long id, T* component){
		for(auto pair : components_){
			if(pair.first == id){
				return;
			}
		}
		components_.insert(std::make_pair(id, component));
		component->parent = id;
	}

	template<class T>
	T* ComponentRegister<T>::GetComponent(unsigned long id){
		auto pair = components_.find(id);
		if(pair == components_.end()){ return nullptr; }
		return pair->second;
	}

	template<class T>
	void ComponentRegister<T>::RemoveComponent(unsigned long id){
		auto pair = components_.find(id);
		if(pair == components_.end()){ return; }
		delete pair->second;
		components_.erase(pair);
	}

	template<class T>
	std::map<unsigned long, T*> ComponentRegister<T>::components_;
}