#ifndef CORE_SERVICE_LOGIC_HPP
#define CORE_SERVICE_LOGIC_HPP

#include <vector>
#include <glm/glm.hpp>
#include "core/service/service.hpp"
#include "core/entity/gameobject/game_object.hpp"

namespace game{

	class Logic : public CoreService{

		public:
			Logic();
			~Logic();

			void Initialize();

			void ClearMemory();
			void Update();

		private:
			std::vector<GameObject*> game_objects_;

			GameObject* SpawnSprite(std::string);
			GameObject* SpawnCamera(glm::vec3);
	};
}

#include "logic.tcc"

#endif
