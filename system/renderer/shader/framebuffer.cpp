#include "framebuffer.hpp"

namespace game{

	GLuint Framebuffer::g_position_depth_ = 0;
	GLuint Framebuffer::g_normal_ = 0;
	GLuint Framebuffer::g_albedo_spec_ = 0;
	GLuint Framebuffer::ssao_blur_color_buffer_ = 0;
	GLuint Framebuffer::bloom_blur_color_buffer_ = 0;
	GLuint Framebuffer::light_flare_color_buffer_ = 0;
}
