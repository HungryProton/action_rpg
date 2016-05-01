#include "component_register.hpp"
#include "common/logger.hpp"
#include "entity/entity.hpp"

namespace game{

	template<class T>
	int ComponentRegister<T>::AttachComponent(unsigned long id, T* component){
		for(auto pair : components_){
			if(pair.first == id){
				return 1;
			}
		}
		components_.insert(std::make_pair(id, component));
		component->parent = id;
		return 0;
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
	void ComponentRegister<T>::CloneFromTo(unsigned long from, unsigned long to){
		T* clone = GetComponent(from)->Clone();
		Entity::AttachComponent<T>(to, clone);
	}

	template<class T>
	std::map<unsigned long, T*> ComponentRegister<T>::components_;
}
