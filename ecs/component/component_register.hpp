#ifndef GAME_ECS_COMPONENT_HPP_
#define GAME_ECS_COMPONENT_HPP_

#include <unordered_map>
#include "../entity/entity.hpp"

namespace game{

	class ecs;

	class BaseComponentRegister{};

	template<class T>
	class ComponentRegister : public BaseComponentRegister{
		friend class ecs;
		private:
			static T* CreateForEntity(Entity);
			static T* GetFromEntity(Entity);
			static void DeleteFromEntity(Entity);
			static Entity GetParent(T*);
			static void ClearMemory();

			static std::unordered_map<unsigned long, T*> components_;
			static bool stored_;
	};
}

#include "component_register.tcc"
#endif //GAME_ECS_COMPONENT_HPP_
