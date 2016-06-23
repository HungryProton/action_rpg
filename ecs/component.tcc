#include "component_register.hpp"
#include "common/logger.hpp"
#include "ecs/entity.hpp"

namespace game{

	template<class T>
	int ComponentRegister<T>::AttachComponent(Entity id, T* component){
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
	T* ComponentRegister<T>::GetComponent(Entity id){
		auto pair = components_.find(id);
		if(pair == components_.end()){ return nullptr; }
		return pair->second;
	}

	template<class T>
	void ComponentRegister<T>::RemoveComponent(Entity id){
		auto pair = components_.find(id);
		if(pair == components_.end()){ return; }
		delete pair->second;
		components_.erase(pair);
	}

	template<class T>
	void ComponentRegister<T>::CloneFromTo(Entity from, Entity to){
		T* clone = GetComponent(from)->Clone();
		Entity::AttachComponent<T>(to, clone);
	}

	template<class T>
	std::map<Entity, T*> ComponentRegister<T>::components_;
}
