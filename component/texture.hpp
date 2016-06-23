#ifndef GAME_COMPONENT_TEXTURE_HPP
#define GAME_COMPONENT_TEXTURE_HPP

#include <string>
#include "common/opengl.hpp"
#include "component/component.hpp"

namespace game{

	struct Texture : public Component{

		GLuint texture;
		int width;
		int height;
		bool transparent;
		glm::vec3 local_scale;

		// ---- Helper methods ---- //
		Texture();
		Texture(Entity);
		Texture(std::string, Entity p=0);
		Texture(Texture*);
		virtual ~Texture(){}
		virtual Texture* Clone();

		bool IsValid();
		void Bind(GLenum);
	};
}

#endif // GAME_COMPONENT_TEXTURE_HPP

