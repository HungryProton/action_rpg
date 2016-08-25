#ifndef GAME_ECS_COMPONENT_HPP_
#define GAME_ECS_COMPONENT_HPP_

#include <unordered_map>
#include <vector>
#include "../entity/entity.hpp"

namespace game{

	class ecs;

	class BaseComponentRegister{};

	template<class T>
	class ComponentRegister : public BaseComponentRegister{
		friend class ecs;
		private:
			template<class...Args>
			static T* CreateForEntity(Entity, Args...);

			static T* GetLastFromEntity(Entity);
			static std::vector<T*> GetAllFromEntity(Entity);

			static void DeleteAllFromEntity(Entity);
			static void DeleteFromEntity(Entity, T*);

			static Entity GetParent(T*);
			static void ClearMemory();

			static std::unordered_map<unsigned long, std::vector<T*>> components_;
			static bool stored_;
	};
}

#include "component_register.tcc"
#endif //GAME_ECS_COMPONENT_HPP_
