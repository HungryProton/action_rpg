#ifndef GAME_SHADER_DEFERRED_LIGHTING_HPP
#define GAME_SHADER_DEFERRED_LIGHTING_HPP

#include "shader.hpp"

namespace game{

	class DeferredLighting : public Shader{
		public:
			DeferredLighting(int, int);
			virtual void Bind();

		protected:


	};
}

#endif //GAME_SHADER_DEFERRED_LIGHTING_HPP
