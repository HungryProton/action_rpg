#ifndef GAME_ENTITY_ENTITY_HPP
#define GAME_ENTITY_ENTITY_HPP

#include <map>
#include "entity_builder.hpp"
#include "entity.hpp"
#include "core/game.hpp"

namespace game{

	class ECS{
		friend Game;
		public:
			static Entity Create();
			static Entity Clone(Entity);
			static void Destroy(Entity);

			template<class T>
			static void AttachComponent(Entity, T*);

			template<class T>
			static T* GetComponent(Entity);

		protected:
			static void ClearMemory();

		private:
			static EntityBuilder builder_;
			static std::map<Entity, std::vector<void(*)(Entity)>> delete_map_;
			static std::map<Entity, std::vector<void(*)(Entity, Entity)>> clone_map_;
	};
}

#include "ecs.tcc"

#endif //GAME_ENTITY_ENTITY_HPP
