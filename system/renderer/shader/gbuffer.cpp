#include "gbuffer.hpp"
#include "service/service.hpp"
#include "service/shader_loader.hpp"
#include "framebuffer.hpp"

namespace game{

	GBuffer::GBuffer(int w, int h) : Shader(w, h){
		InitializeShader();
		CreateAndBindFramebuffer();

		CreatePositionBuffer();
		CreateNormalBuffer();
		CreateColorBuffer();
		DefineAttachments();
		CreateDepthBuffer();

		CheckFramebufferValidity();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GBuffer::InitializeShader(){
		program_ = Service::Get<ShaderLoader>()->GetShader("shader/g_buffer.vs",
				"shader/g_buffer.frag");
	}

	void GBuffer::CreateAndBindFramebuffer(){
		glGenFramebuffers(1, &g_buffer_);
		glBindFramebuffer(GL_FRAMEBUFFER, g_buffer_);
	}

	void GBuffer::CreatePositionBuffer(){
		GenerateAndBindTexture(&g_position_depth_);
		Framebuffer::g_position_depth_ = g_position_depth_;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width_, height_, 0, GL_RGBA,
		GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		this->g_position_depth_, 0);
	}

	void GBuffer::CreateNormalBuffer(){
		GenerateAndBindTexture(&g_normal_);
		Framebuffer::g_normal_ = g_normal_;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width_, height_, 0, GL_RGB,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
		this->g_normal_, 0);
	}

	void GBuffer::CreateColorBuffer(){
		GenerateAndBindTexture(&g_albedo_spec_);
		Framebuffer::g_albedo_spec_ = g_albedo_spec_;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
		GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
		this->g_albedo_spec_, 0);
	}

	void GBuffer::CreateDepthBuffer(){
    glGenRenderbuffers(1, &(depth_buffer_));
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				GL_RENDERBUFFER, depth_buffer_);
	}

	// - Tell OpenGL which color attachments we’ll use (of this framebuffer)
	// for rendering
	void GBuffer::DefineAttachments(){
		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
	 	GL_COLOR_ATTACHMENT2};
		glDrawBuffers(3, attachments);
	}

	void GBuffer::Bind(){
		glBindFramebuffer(GL_FRAMEBUFFER, g_buffer_);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_);
	}
}
