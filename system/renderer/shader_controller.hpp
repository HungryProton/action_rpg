#ifndef GAME_SYSTEM_RENDERER_SHADER_CONTROLLER_HPP_
#define GAME_SYSTEM_RENDERER_SHADER_CONTROLLER_HPP_

#include <map>
#include "common/opengl.hpp"
#include "component/drawable.hpp"
#include "shader/shader.hpp"

namespace game{
	/*
	 * CAUTION : This class requires a valid OpenGL context to work
	 */

	enum class Program{NONE, G_BUFFER, SSAO, HBLUR, VBLUR,
										 BLOOM, LIGHT_FLARE, LIGHTING};

	class ShaderController{
		public:
			ShaderController();
			~ShaderController();

			void Initialize(int, int);
			void Enable(Program);
			void RenderToScreen();
			GLuint GetUniformLocation(std::string);
			void UniformMatrix4fv(std::string, glm::mat4);
			void Uniform2f(std::string, float, float);
			void Uniform3f(std::string, glm::vec3);
			void Uniform1i(std::string, int);
			void Uniform1iv(std::string, int, int*);
			void Uniform1fv(std::string, int, float*);
			void Uniform3fv(std::string, int, float*);

		private:
			Drawable* screen_quad_;
			std::map<Program, Shader*> shaders_;
			int current_program_;
			int width_;
			int height_;
	};
}

#endif //GAME_SYSTEM_RENDERER_SHADER_CONTROLLER_HPP_
