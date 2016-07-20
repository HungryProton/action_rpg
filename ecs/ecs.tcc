#include "ecs.hpp"
#include "ecs/node/node.hpp"
#include "ecs/component/component_register.hpp"
#include "common/logger.hpp"

namespace game{

	template<class T>
	T* ecs::CreateComponentForEntity(Entity e){
		// Store a pointer to the register clearMemory function to call it at
		// the end of the program.
		if(!ComponentRegister<T>::stored_){
			component_registers_clear_fcn_.push_back(ComponentRegister<T>::ClearMemory);
			component_registers_delete_fcn_.push_back(ComponentRegister<T>::DeleteFromEntity);
			ComponentRegister<T>::stored_ = true;
		}
		T* newly_created_component = ComponentRegister<T>::CreateForEntity(e);
		ecs::NotifyEntityHasChanged(e);
		return newly_created_component;
	}

	template<class T>
	void ecs::RemoveComponentFromEntity(Entity e){
		ComponentRegister<T>::DeleteFromEntity(e);
		ecs::NotifyEntityHasChanged(e);
	}

	template<class T>
	T* ecs::GetComponentFromEntity(Entity e){
		return ComponentRegister<T>::GetFromEntity(e);
	}

	template<class T>
	Entity ecs::GetParentOfComponent(T* component){
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
