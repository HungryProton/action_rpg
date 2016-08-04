#ifndef GAME_WORLD_HPP_
#define GAME_WORLD_HPP_

#include <string>
#include <vector>

namespace game{

	class World{
		public:
			static void Initialize(double);
			static void GenerateNew();
			static void LoadFromFile();
			static void SaveToFile(std::string);

		private:
			static double seed_;
	};
}

#endif //GAME_WORLD_HPP_
