#ifndef GAME_ECS_HPP_
#define GAME_ECS_HPP_

#include <vector>
#include "component/component_register.hpp"
#include "entity/entity.hpp"
#include "entity/entity_builder.hpp"

namespace game{

	class ecs{
		public:
			static Entity CreateEntity();
			static void DestroyEntity(Entity);

			template<class ...>
			static void CreateSignature();
			template<class ...>
			static std::vector<Entity> GetEntitiesWithComponents();

			static void NotifyEntityHasChanged(Entity);
			static void NotifyEntityWasDeleted(Entity);

			template<class T, class...Args>
			static T* CreateComponent(Entity, Args...);

			template<class T>
			static void RemoveComponent(Entity);
			template<class T>
			static T* GetComponent(Entity);
			template<class T>
			static Entity GetParentOf(T*);

			static void ClearMemory();

		private:
			static std::vector<void(*)(Entity)> node_update_fcn_;
			static std::vector<void(*)(Entity)> node_delete_fcn_;
			static std::vector<void(*)()> nodes_clear_fcn_;
			static std::vector<void(*)()> component_registers_clear_fcn_;
			static std::vector<void(*)(Entity)> component_registers_delete_fcn_;
			static EntityBuilder entity_builder_;
	};
}

#include "ecs.tcc"
#endif //GAME_ECS_HPP_
