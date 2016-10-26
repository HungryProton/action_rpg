#ifndef GAME_SYSTEM_RENDERER_SHADER_BLUR_HPP
#define GAME_SYSTEM_RENDERER_SHADER_BLUR_HPP

#include "shader.hpp"

namespace game{

	class Blur : public Shader{
		public:
			Blur(int, int, GLuint*, GLuint*);
			virtual void Bind();

		private:
			void InitializeShader();
			void CreateAndBindFramebuffer();
			GLuint* source_buffer_;
			GLuint* target_buffer_;
			GLuint buffer_;
	};
}

#endif //GAME_SYSTEM_RENDERER_SHADER_BLUR_HPP
