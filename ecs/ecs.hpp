#ifndef GAME_ECS_HPP_
#define GAME_ECS_HPP_

#include <vector>
#include "component/component_register.hpp"
#include "entity/entity.hpp"
#include "entity/entity_builder.hpp"
#include "node/node.hpp"

namespace game{

	class ecs{
		public:
			static Entity CreateEntity();
			static void DestroyEntity();

			template<class ...>
			static void CreateSignature();
			template<class ...>
			static std::vector<Entity> GetEntitiesWithComponents();
			static void NotifyEntityHasChanged(Entity);
			static void NotifyEntityWasDeleted(Entity);

			template<class T>
			static T* CreateComponentForEntity(Entity);
			template<class T>
			static void RemoveComponentFromEntity(Entity);

			static void ClearMemory();

		private:
			static std::vector<BaseNode*> nodes_;
			static std::vector<void(*)()> component_registers_clear_fcn_;
			static EntityBuilder entity_builder_;
	};
}

#include "ecs.tcc"
#endif //GAME_ECS_HPP_
