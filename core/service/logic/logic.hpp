#ifndef CORE_SERVICE_LOGIC_HPP
#define CORE_SERVICE_LOGIC_HPP

#include <vector>
#include <glm/glm.hpp>
#include "core/service/service.hpp"
#include "core/entity/game_object.hpp"

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

			GameObject* SpawnSprite(std::string, glm::vec3);
			void SpawnMultipleSprite(std::string, int);
			GameObject* SpawnCamera(glm::vec3);
			GameObject* SpawnMesh(std::string);
			GameObject* SpawnPlayer(std::string);
	};
}

#include "logic.tcc"

#endif
