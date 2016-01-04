#ifndef GAME_CORE_SERVICE_SHADER_HELPER_HPP
#define GAME_CORE_SERVICE_SHADER_HELPER_HPP

#include <map>
#include <string>
#include "tools/opengl.hpp"
#include "core/service/service.hpp"

namespace game{

	class ShaderHelper : public Service{
		public:
			ShaderHelper();
			~ShaderHelper();
			void ClearMemory();
			GLuint GetShader(std::string, std::string);

		private:
			GLuint LoadShaders(const char*, const char*);
			std::map<std::string, GLuint> shaders;
	};
}

#endif //GAME_CORE_SERVICE_SHADER_HELPER_HPP
