#ifndef GAME_SYSTEM_RENDERER_SHADER_GBUFFER_HPP
#define GAME_SYSTEM_RENDERER_SHADER_GBUFFER_HPP

#include "common/opengl.hpp"
#include "shader.hpp"

namespace game{

	class GBuffer : public Shader{
		public:
			GBuffer(int, int);
			virtual void Bind();

		protected:
			GLuint g_buffer_;
			GLuint g_position_depth_;
			GLuint g_normal_;
			GLuint g_albedo_spec_;
			GLuint depth_buffer_;

		private:
			void InitializeShader();
			void CreateAndBindFramebuffer();
			void CreatePositionBuffer();
			void CreateColorBuffer();
			void CreateNormalBuffer();
			void CreateDepthBuffer();
			void DefineAttachments();
	};
}
#endif //GAME_SYSTEM_RENDERER_SHADER_GBUFFER_HPP
