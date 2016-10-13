#ifndef GAME_SHADER_FRAMEBUFFER_HPP_
#define GAME_SHADER_FRAMEBUFFER_HPP_

#include "common/opengl.hpp"

namespace game{

	class Framebuffer{
		public:
			static GLuint g_position_depth_;
			static GLuint g_normal_;
			static GLuint g_albedo_spec_;
			static GLuint ssao_color_buffer_;
			static GLuint ssao_blur_color_buffer_;
			static GLuint bloom_color_buffer_;
			static GLuint light_flare_color_buffer_;
	};
}

#endif //GAME_SHADER_FRAMEBUFFER_HPP_
