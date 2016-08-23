#include "ssao.hpp"
#include <vector>
#include "common/random.hpp"
#include "common/math.hpp"
#include "common/logger.hpp"
#include "service/service.hpp"
#include "service/shader_loader.hpp"
#include "framebuffer.hpp"

namespace game{

	SSAO::SSAO(int w, int h) : Shader(w, h){
		InitializeShader();
		GenerateHemisphereKernel(1);
		GenerateNoise();
		GenerateFramebuffer();
	}

	void SSAO::Bind(){
		glBindFramebuffer(GL_FRAMEBUFFER, buffer_);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_);
	}

	void SSAO::InitializeShader(){
		program_ = Service::Get<ShaderLoader>()->GetShader("shader/ssao.vs",
				"shader/ssao.frag");
	}

	void SSAO::GenerateHemisphereKernel(unsigned int kernel_size){

		std::vector<glm::vec3> ssao_kernel;
		for(GLuint i = 0; i < kernel_size; i++){
			glm::vec3 sample(
					Random::NextFloat(2.f) - 1.f,
					Random::NextFloat(2.f) - 1.f,
					Random::NextFloat(0.8f) + 0.2f // Prevent samples too much aligned
				 	);														 //	with the surface;
			sample = glm::normalize(sample);

			GLfloat scale = GLfloat(i) / kernel_size;
			scale = Math::lerp(0.1f, 1.0f, scale * scale);
			sample *= scale;
			ssao_kernel.push_back(sample);
		}

		// Save kernel in a 1D texture
		glGenTextures(1, &kernel_);
		glBindTexture(GL_TEXTURE_1D, kernel_);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB16F, kernel_size, 0, GL_RGB, GL_FLOAT,
		&ssao_kernel[0]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void SSAO::GenerateNoise(){
		std::vector<glm::vec3> ssao_noise;
		for(GLuint i = 0; i < 16; i++){
			glm::vec3 noise(
					Random::NextFloat(2.f) - 1.f,
					Random::NextFloat(2.f) - 1.f,
					0.f);
			ssao_noise.push_back(glm::normalize(noise));
		}

		// Save noise in texture
		glGenTextures(1, &noise_);
		glBindTexture(GL_TEXTURE_2D, noise_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT,
		&ssao_noise[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void SSAO::GenerateFramebuffer(){
		glGenFramebuffers(1, &buffer_);
		glBindFramebuffer(GL_FRAMEBUFFER, buffer_);

		glGenTextures(1, &(Framebuffer::ssao_color_buffer_));
		glBindTexture(GL_TEXTURE_2D, Framebuffer::ssao_color_buffer_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width_, height_, 0, GL_RGB,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		Framebuffer::ssao_color_buffer_, 0);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG(CRITICAL) << "SSAO Framebuffer not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
