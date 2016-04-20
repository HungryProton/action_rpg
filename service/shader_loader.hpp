#ifndef GAME_CORE_SERVICE_SHADER_HELPER_HPP
#define GAME_CORE_SERVICE_SHADER_HELPER_HPP

#include <map>
#include <string>
#include "common/opengl.hpp"
#include "service_worker.hpp"

namespace game{

	class ShaderLoader : public ServiceWorker{
		public:
			ShaderLoader();
			~ShaderLoader();
			void ClearMemory();
			GLuint GetShader(std::string, std::string);

		private:
			GLuint LoadShaders(const char*, const char*);
			std::map<std::string, GLuint> shaders;
	};
}

#endif //GAME_CORE_SERVICE_SHADER_HELPER_HPP
