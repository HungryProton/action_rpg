#include "component_register.hpp"
#include "ecs/entity/entity.hpp"
#include "common/logger.hpp"

namespace game{

	template<class T>
	T* ComponentRegister<T>::CreateForEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair != components_.end()){
			return pair->second;
		}
		T* component = new T();
		components_.insert(std::make_pair(e.uid, component));
		return component;
	}

	template<class T>
	T* ComponentRegister<T>::GetFromEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return nullptr; }
		return pair->second;
	}

	template<class T>
	void ComponentRegister<T>::DeleteFromEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return; }
		delete pair->second;
		components_.erase(pair);
	}

	template<class T>
	Entity ComponentRegister<T>::GetParent(T* component){
		Entity e = Entity();
		for(auto pair : components_){
			if(pair.second == component){
				e.uid = pair.first;
				break;
			}
		}
		return e;
	}

	template<class T>
	void ComponentRegister<T>::ClearMemory(){
		for(auto pair : components_){
			delete pair.second;
		}
		components_.clear();
	}

	template<class T>
	std::unordered_map<unsigned long, T*> ComponentRegister<T>::components_;

	template<class T>
	bool ComponentRegister<T>::stored_ = false;
}
