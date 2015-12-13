#ifndef GAME_CORE_SERVICE_INPUT_HPP
#define GAME_CORE_SERVICE_INPUT_HPP

#include <vector>
#include <string>
#include "core/service/service.hpp"
#include "tools/opengl.hpp"

namespace game{

	class Input : public CoreService{
		public:
			Input();
			~Input();

			void Initialize(GLFWwindow*);
			void ClearMemory();
			void Update();

		private:
			void LoadKeymapFromFile(std::string);

			GLFWwindow* window_;
	};
}

#endif //GAME_CORE_SERVICE_INPUT_HPP
