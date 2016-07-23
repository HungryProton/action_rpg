#ifndef GAME_WORLD_HPP_
#define GAME_WORLD_HPP_

namespace game{

	class World{
		public:
			static void GenerateNew();
			static void LoadFromFile();
			static void SaveToFile();
	};
}

#endif //GAME_WORLD_HPP_
