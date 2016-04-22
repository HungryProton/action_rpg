#ifndef GAME_SYSTEM_RENDERER_CONTEXT_CONTROLLER_HPP_
#define GAME_SYSTEM_RENDERER_CONTEXT_CONTROLLER_HPP_

#include "common/opengl.hpp"

namespace game{

	class ContextController{
		public:
			ContextController();
			~ContextController();

			void Initialize();
			GLFWwindow* GetWindow();
			void SwapBuffers();
			bool IsContextValid();

		private:
			int InitializeGLFW();
			int InitializeOpenGL();
			int LoadConfigurationFromFile();
			static void GLFWErrorCallback(int, const char*);

			std::string configuration_file_path_;
			GLFWwindow* window_;
			bool context_validity_;
	};
}
#endif //GAME_SYSTEM_RENDERER_CONTEXT_CONTROLLER_HPP_
