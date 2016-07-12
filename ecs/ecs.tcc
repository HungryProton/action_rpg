#include "ecs.hpp"
#include "ecs/node/node.hpp"
#include "ecs/component/component_register.hpp"

namespace game{

	template<class... components>
	void ecs::CreateSignature(){
		Node<components...>* node = new Node<components...>();
		nodes_.push_back(node);
	}

	template<class T>
	T* ecs::CreateComponentForEntity(Entity e){
		// Store a pointer to the register clearMemory function to call it at
		// the end of the program.
		if(!ComponentRegister<T>::stored_){
			component_registers_clear_fcn_.push_back(ComponentRegister<T>::ClearMemory);
			ComponentRegister<T>::stored_ = true;
		}

		return ComponentRegister<T>::CreateForEntity(e);
	}

	template<class... Types>
	std::vector<Entity> ecs::GetEntitiesWithComponents(){

	}
}
