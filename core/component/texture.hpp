#ifndef GAME_COMPONENT_TEXTURE_HPP
#define GAME_COMPONENT_TEXTURE_HPP

#include <string>
#include "tools/opengl.hpp"
#include "core/component/component.hpp"

namespace game{

	struct Texture : public Component{

		GLuint texture;
		int width;
		int height;
		bool transparent;
		glm::vec3 local_scale;

		// ---- Helper methods ---- //
		Texture();
		Texture(GameObject*);
		Texture(std::string, GameObject* p=nullptr);
		Texture(Texture*);
		bool IsValid();
		void Bind(GLenum);
		virtual Texture* Clone();
	};
}

#endif // GAME_COMPONENT_TEXTURE_HPP

