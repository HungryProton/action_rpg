#include "shader.hpp"
#include "common/opengl.hpp"
#include "common/logger.hpp"

namespace game{

	Shader::Shader(int w, int h){
		program_ = 0;
		width_ = w;
		height_ = h;
	}

	Shader::~Shader(){
		glDeleteProgram(program_);
	}

	GLuint Shader::GetProgram(){
		return program_;
	}

	void Shader::GenerateTexture(GLuint* tex){
		glGenTextures(1, tex);
	}

	void Shader::BindTexture(GLuint tex){
		glBindTexture(GL_TEXTURE_2D, tex);
	}

	void Shader::GenerateAndBindTexture(GLuint* tex){
		GenerateTexture(tex);
		BindTexture(*tex);
	}

	int Shader::CheckFramebufferValidity(){
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			LOG(ERROR) << "Framebuffer not complete!" << std::endl;
			return 1;
		}
		return 0;
	}
}
