#ifndef CORE_ENTITY_COMPONENT_DRAWABLE_HPP
#define CORE_ENTITY_COMPONENT_DRAWABLE_HPP

#include "common/opengl.hpp"
#include "component.hpp"

namespace game{

	struct Drawable : public Component{
		GLenum draw_type;
		GLuint vao;
		GLuint shader;
		int vertex_amount;
		int offset;
		float alpha;

		Drawable();
		Drawable(unsigned long);
		Drawable(Drawable*);
		Drawable* Clone();
	};
}

#endif //CORE_ENTITY_COMPONENT_DRAWABLE_HPP
