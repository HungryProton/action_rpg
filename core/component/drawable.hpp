#ifndef CORE_ENTITY_COMPONENT_DRAWABLE_HPP
#define CORE_ENTITY_COMPONENT_DRAWABLE_HPP

#include "tools/opengl.hpp"
#include "component.hpp"

namespace game{

	struct Drawable : public Component{
		GLenum draw_type;
		GLuint vao;
		GLuint shader;
		int vertex_amount;
		int offset;
		int amount;

		Drawable();
		Drawable(GameObject*);
		Drawable(Drawable*);
		Drawable* Clone();
		virtual void Update();
	};
}

#endif //CORE_ENTITY_COMPONENT_DRAWABLE_HPP
