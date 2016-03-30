#ifndef CORE_SERVICE_GAME_OBJECT_BUILDER_HPP
#define CORE_SERVICE_GAME_OBJECT_BUILDER_HPP

#include <map>
#include <string>
#include "core/entity/game_object.hpp"
#include "core/service/service.hpp"

namespace game{

	class GameObjectBuilder : public Service{
		public:
			GameObjectBuilder();
			~GameObjectBuilder();

			void ClearMemory();
			GameObject* CreateBlank();
			GameObject* CreateFromPreset(std::string);

			void RegisterPreset(std::string, GameObject*);
			GameObject* LoadAnimatedSprite(std::string);

		private:
			std::map<std::string, GameObject*> presets_;

	};
}

#endif //CORE_SERVICE_GAME_OBJECT_BUILDER_HPP
