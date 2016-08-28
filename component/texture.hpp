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
		// Used to display only a portion of the texture
		glm::vec2 shift;
		glm::vec2 ratio;

		// ---- Helper methods ---- //
		Texture();
		Texture(std::string);

		bool IsValid();
		void Bind(GLenum);
	};
}

#endif // GAME_COMPONENT_TEXTURE_HPP

