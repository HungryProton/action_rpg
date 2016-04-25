#ifndef GAME_SYSTEM_RENDERER_SHADER_CONTROLLER_HPP_
#define GAME_SYSTEM_RENDERER_SHADER_CONTROLLER_HPP_

#include "common/opengl.hpp"
#include "component/drawable.hpp"

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

			void Initialize();
			void Enable(Program);
			void RenderToScreen();

		private:
			Drawable* screen_quad_;

	};
}

#endif //GAME_SYSTEM_RENDERER_SHADER_CONTROLLER_HPP_
