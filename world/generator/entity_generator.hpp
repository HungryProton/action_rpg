#ifndef GAME_WORLD_BUILDER_ENTITY_GENERATOR_HPP_
#define GAME_WORLD_BUILDER_ENTITY_GENERATOR_HPP_

namespace game{

	class EntityGenerator{
		public:
			EntityGenerator();
			~EntityGenerator();

			unsigned long SpawnPlayer();
			unsigned long SpawnCamera();
			unsigned long SpawnRandom();

		private:

	};
}

#endif //GAME_WORLD_BUILDER_ENTITY_GENERATOR_HPP_
