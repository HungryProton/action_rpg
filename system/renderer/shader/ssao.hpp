#ifndef GAME_SYSTEM_RENDERER_SHADER_SSAO_
#define GAME_SYSTEM_RENDERER_SHADER_SSAO_

#include "shader.hpp"

namespace game{

	class SSAO : public Shader{
		public:
			SSAO(int, int);
			virtual void Bind();

		protected:
			GLuint buffer_;
			GLuint kernel_;
			GLuint noise_;

		private:
			void InitializeShader();
			void GenerateHemisphereKernel(unsigned int);
			void GenerateNoise();
			void GenerateFramebuffer();

	};
}

#endif //GAME_SYSTEM_RENDERER_SHADER_SSAO_
