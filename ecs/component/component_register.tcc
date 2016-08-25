#include "component_register.hpp"
#include "ecs/entity/entity.hpp"
#include "common/logger.hpp"

namespace game{

	template<class T>
	template<class... Args>
	T* ComponentRegister<T>::CreateForEntity(Entity e, Args... args){
		T* component = new T(args...);

		auto pair = components_.find(e.uid);
		if(pair != components_.end()){	// If entity already have components, add the new one to the list
			pair->second.push_back(component);
		} else {		// Otherwise, create the list
			std::vector<T*> vector;
			vector.push_back(component);
			components_.insert(std::make_pair(e.uid, vector));
		}
		return component;
	}

	template<class T>
	T* ComponentRegister<T>::GetLastFromEntity(Entity e){
		auto list = GetAllFromEntity(e);
		if(list.empty()){ return nullptr; }
		return list.back();
	}

	template<class T>
	std::vector<T*> ComponentRegister<T>::GetAllFromEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return std::vector<T*>(); }
		return pair->second;
	}

	template<class T>
	void ComponentRegister<T>::DeleteAllFromEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return; }
		for(T* component : pair->second){
			delete component;
		}
		components_.erase(pair);
	}

	template<class T>
	void ComponentRegister<T>::DeleteFromEntity(Entity e, T* component){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return; }
		for(unsigned int i = 0; i < pair->second.size(); i++){
			if(pair->second[i] == component){
				pair->second.erase(pair->second.begin() + i);
				return;
			}
		}
	}

	template<class T>
	Entity ComponentRegister<T>::GetParent(T* component){
		Entity e = Entity();
		for(auto pair : components_){
			for(T* c: pair.second){
				if(c == component){
					e.uid = pair.first;
					break;
				}
			}
		}
		return e;
	}

	template<class T>
	void ComponentRegister<T>::ClearMemory(){
		for(auto pair : components_){
			for(T* component : pair.second){
				delete component;
			}
		}
		components_.clear();
	}

	template<class T>
	std::unordered_map<unsigned long, std::vector<T*>> ComponentRegister<T>::components_;

	template<class T>
	bool ComponentRegister<T>::stored_ = false;
}
