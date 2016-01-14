#ifndef GAME_TEST_COMMON_HPP
#define GAME_TEST_COMMON_HPP

#include "tools/opengl.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

namespace game{

	class Common{

		public:
			static void CreateOpenGLContext();
			static void DestroyOpenGLContext();
			static void SendInputMessage(Command);

		private:
			static GLFWwindow* window_;

	};
}

#endif //GAME_TEST_COMMON_HPP
