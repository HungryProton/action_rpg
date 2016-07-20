#ifndef GAME_COMPONENT_TEXTURE_HPP
#define GAME_COMPONENT_TEXTURE_HPP

#include <string>
#include "common/opengl.hpp"

namespace game{

	struct Texture{
		GLuint texture;
		int width;
		int height;
		bool transparent;
		glm::vec3 local_scale;

		// ---- Helper methods ---- //
		Texture();
		Texture(std::string);

		bool IsValid();
		void Bind(GLenum);
	};
}

#endif // GAME_COMPONENT_TEXTURE_HPP

