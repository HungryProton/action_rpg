#include "component.hpp"
#include "ecs/entity.hpp"

namespace game{

	template<class T>
	T* Component<T>::CreateForEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair != components_.end()){
			return pair.second;
		}
		T* component = new T();
		components_.insert(std::make_pair(e.uid, component));
		return component;
	}

	template<class T>
	T* Component<T>::GetFromEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return nullptr; }
		return pair->second;
	}

	template<class T>
	void Component<T>::DeleteFromEntity(Entity e){
		auto pair = components_.find(e.uid);
		if(pair == components_.end()){ return; }
		delete pair->second;
		components_.erase(pair);
	}

	template<class T>
	std::unordered_map<unsigned long, T*> Component<T>::components_;
}
