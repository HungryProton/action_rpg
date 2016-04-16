#ifndef GAME_ENTITY_ENTITY_HPP
#define GAME_ENTITY_ENTITY_HPP

#include "entity_builder.hpp"

namespace game{

	class Entity{
		public:
			static unsigned long Create();
			static void Destroy(unsigned long);
			template<class T>
			static void AddComponent(unsigned long, T);

		private:
			static EntityBuilder builder;
	};
}

#endif //GAME_ENTITY_ENTITY_HPP
