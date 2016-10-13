#include "blur.hpp"
#include "service/service.hpp"
#include "service/shader_loader.hpp"
#include "common/logger.hpp"

namespace game{

	Blur::Blur(int w, int h, GLuint* src, GLuint* dest) : Shader(w, h){
		source_buffer_ = src;
		target_buffer_ = dest;
		InitializeShader();
	}

	void Blur::InitializeShader(){
		program_ = Service::Get<ShaderLoader>()->GetShader("shader/g_buffer.vs",
				"shader/g_buffer.frag");
		CreateAndBindFramebuffer();
	}

	void Blur::CreateAndBindFramebuffer(){
		glGenFramebuffers(1, target_buffer_);
		glBindFramebuffer(GL_FRAMEBUFFER, *target_buffer_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *target_buffer_, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOG(CRITICAL) << "Blur Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Blur::Bind(){
		glBindFramebuffer(GL_FRAMEBUFFER, *target_buffer_);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program_);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *source_buffer_);
	}
}

