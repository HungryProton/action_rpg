#include "ecs.hpp"
#include "ecs/node/node.hpp"
#include "ecs/component/component_register.hpp"
#include "common/logger.hpp"

namespace game{

	template<class T, class...Args>
	T* ecs::CreateComponent(Entity e, Args... args){
		// Store a pointer to the register clearMemory function to call it at
		// the end of the program.
		if(!ComponentRegister<T>::stored_){
			component_registers_clear_fcn_.push_back(ComponentRegister<T>::ClearMemory);
			component_registers_delete_fcn_.push_back(ComponentRegister<T>::DeleteAllFromEntity);
			ComponentRegister<T>::stored_ = true;
		}
		T* newly_created_component = ComponentRegister<T>::CreateForEntity(e, args...);
		ecs::NotifyEntityHasChanged(e);
		return newly_created_component;
	}

	template<class T>
	void ecs::RemoveAllComponent(Entity e){
		ComponentRegister<T>::DeleteAllFromEntity(e);
		ecs::NotifyEntityHasChanged(e);
	}

	template<class T>
	std::vector<T*> ecs::GetAllComponents(Entity e){
		return ComponentRegister<T>::GetAllFromEntity(e);
	}

	template<class T>
	T* ecs::GetComponent(Entity e){
		return ComponentRegister<T>::GetLastFromEntity(e);
	}

	template<class T>
	Entity ecs::GetParentOf(T* component){
		return ComponentRegister<T>::GetParent(component);
	}

	template<class... Components>
	void ecs::CreateSignature(){
		node_update_fcn_.push_back(Node<Components...>::UpdateListWith);
		node_delete_fcn_.push_back(Node<Components...>::DeleteEntityFromList);
		nodes_clear_fcn_.push_back(Node<Components...>::ClearMemory);
	}

	template<class... Components>
	std::vector<Entity> ecs::GetEntitiesWithComponents(){
		return Node<Components...>::GetEntityList();
	}
}
