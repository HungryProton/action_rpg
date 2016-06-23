#ifndef GAME_ENTITY_FACTORY_HPP_
#define GAME_ENTITY_FACTORY_HPP_

#include <string>
#include <map>

namespace game{

	class EntityFactory{
		public:
			static void LoadInitialPresets();
			static unsigned long CreateFromPreset(std::string);
			static void RegisterPreset(std::string, unsigned long);

		private:
			static std::map<std::string, unsigned long> presets_;
			static void GeneratePlayerPreset();
			static void GenerateRockPreset();
			static void GenerateCameraPreset();
	};
}
#endif //GAME_ENTITY_FACTORY_HPP_
