#ifndef GAME_ENTITY_ENTITY_HPP
#define GAME_ENTITY_ENTITY_HPP

#include <map>
#include "entity_builder.hpp"
#include "core/game.hpp"

namespace game{

	class Entity{
		friend Game;
		public:
			static unsigned long Create();
			static void Destroy(unsigned long);

			template<class T>
			static void AttachComponent(unsigned long, T*);

			template<class T>
			static T* GetComponent(unsigned long);

		private:
			static void ClearMemory();
			static EntityBuilder builder_;
			static std::map<unsigned long, std::vector<void(*)(unsigned long)>> delete_map_;
	};
}

#include "entity.tcc"

#endif //GAME_ENTITY_ENTITY_HPP
