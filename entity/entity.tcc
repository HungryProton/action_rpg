#include "entity.hpp"
#include "component_register.hpp"

namespace game{

	template<class T>
	T* Entity::GetComponent(unsigned long id){
		return ComponentRegister<T>::GetComponent(id);
	}

	template<class T>
	void Entity::AddComponent(unsigned long id, T* component){
		ComponentRegister<T>::AddComponent(id, component);
	}
}
