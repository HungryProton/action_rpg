#ifndef GAME_CORE_SERVICE_INPUT_HPP
#define GAME_CORE_SERVICE_INPUT_HPP

#include <map>
#include <string>
#include "../system.hpp"
#include "common/opengl.hpp"
#include "messaging/concrete_messages/input_message.hpp"

namespace game{

	class Input : public System{
		public:
			Input();
			~Input();

			void Initialize(GLFWwindow*);
			virtual void BeforeUpdate();

		private:
			void LoadKeymapFromFile(std::string);
			void LoadDefaultKeymap();
			void AddEntryInKeymap(int, Command);
			void SendCommandForKey(int, Command);
			KeyStatus GetKeyStatus(int);
			void DefineCursorParameters(GLFWwindow*);
			static void OnCursorMove(GLFWwindow*, double, double);
			static glm::vec2 GetPositionFromScreenCoordinates(GLFWwindow*, int, int);

			GLFWwindow* window_;
			std::map<int, Command> keymap_;
			std::map<int, int> previous_keys_status_;
			int first_modifier_code;
			int second_modifier_code;
	};
}

#endif //GAME_CORE_SERVICE_INPUT_HPP
