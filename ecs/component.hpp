#ifndef GAME_ENTITY_COMPONENT_REGISTER_HPP
#define GAME_ENTITY_COMPONENT_REGISTER_HPP

#include <map>

namespace game{

	template<class T>
	class ComponentRegister{
		public:
			static int AttachComponent(Entity, T*);
			static T* GetComponent(Entity);
			static void RemoveComponent(Entity);
			static void CloneFromTo(Entity, Entity);

		private:
			static std::map<Entity, T*> components_;
	};
}

#include "component_register.tcc"
#endif //GAME_ENTITY_COMPONENT_REGISTER_HPP
