#include "deferred_lighting.hpp"
#include "service/service.hpp"
#include "service/shader_loader.hpp"
#include "framebuffer.hpp"

namespace game{

	DeferredLighting::DeferredLighting(int w, int h) : Shader(w, h){
		program_ = Service::Get<ShaderLoader>()->GetShader("shader/deferred_shading.vs",
				"shader/deferred_shading.frag");

		glUseProgram(program_);
		glUniform1i( glGetUniformLocation(program_, "gPositionDepth"), 0);
		glUniform1i( glGetUniformLocation(program_, "gNormal"), 1);
		glUniform1i( glGetUniformLocation(program_, "gAlbedoSpec"), 2);
		glUniform1i( glGetUniformLocation(program_, "ssao"), 3);
		glUniform1i( glGetUniformLocation(program_, "bloom"), 4);
		glUniform1i( glGetUniformLocation(program_, "flare"), 5);
	}

	void DeferredLighting::Bind(){
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(program_);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Framebuffer::g_position_depth_);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, Framebuffer::g_normal_);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, Framebuffer::g_albedo_spec_);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, Framebuffer::ssao_color_buffer_);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, Framebuffer::bloom_color_buffer_);
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, Framebuffer::light_flare_color_buffer_);
	}
}
