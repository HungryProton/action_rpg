#ifndef GAME_WORLD_BUILDER_ENTITY_GENERATOR_HPP_
#define GAME_WORLD_BUILDER_ENTITY_GENERATOR_HPP_

namespace game{

	class EntityGenerator{
		public:
			EntityGenerator();
			~EntityGenerator();

			Entity SpawnPlayer();
			Entity SpawnCamera();
			Entity SpawnRandom();

		private:

	};
}

#endif //GAME_WORLD_BUILDER_ENTITY_GENERATOR_HPP_
