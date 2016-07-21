#ifndef GAME_SYSTEM_RENDERER_SHADER_HPP
#define GAME_SYSTEM_RENDERER_SHADER_HPP

#include "common/opengl.hpp"

namespace game{

	class Shader{
		public:
			Shader(int, int);
			~Shader();
			virtual GLuint GetProgram() final;
			virtual void Bind() = 0;

		protected:
			int CheckFramebufferValidity();

			void GenerateTexture(GLuint*);
			void BindTexture(GLuint);
			void GenerateAndBindTexture(GLuint*);

			GLuint program_;
			int width_;
			int height_;
	};
}

#endif //GAME_SYSTEM_RENDERER_SHADER_HPP
