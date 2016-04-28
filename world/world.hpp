#ifndef GAME_WORLD_HPP_
#define GAME_WORLD_HPP_

#include "generator/entity_generator.hpp"

namespace game{

	class World{
		public:
			static void GenerateNew();
			static void LoadFromFile();
			static void SaveToFile();

		private:
			static EntityGenerator entity_generator_;
	};
}

#endif //GAME_WORLD_HPP_
