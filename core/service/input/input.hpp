#ifndef GAME_CORE_SERVICE_INPUT_HPP
#define GAME_CORE_SERVICE_INPUT_HPP

#include <map>
#include <string>
#include "core/service/service.hpp"
#include "tools/opengl.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

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
			void LoadDefaultKeymap();
			void AddEntryInKeymap(int, Command);
			void SendCommandForKey(int, Command);
			KeyStatus GetKeyStatus(int);

			GLFWwindow* window_;
			std::map<int, Command> keymap_;
			std::map<int, int> previous_keys_status_;
			int modifier_code;
	};
}

#endif //GAME_CORE_SERVICE_INPUT_HPP
