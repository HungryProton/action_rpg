#ifndef CORE_ENTITY_COMPONENT_DRAWABLE_HPP
#define CORE_ENTITY_COMPONENT_DRAWABLE_HPP

#include "common/opengl.hpp"
#include "component.hpp"

namespace game{

	enum class DrawableType{NONE, SPRITE, MESH};

	struct Drawable : public Component{
		DrawableType type;
		GLenum draw_type;
		GLuint vao;
		GLuint shader;
		int vertex_amount;
		int offset;
		float alpha;

		Drawable();
		virtual ~Drawable();
		Drawable(Entity);
		Drawable(Drawable*);
		Drawable* Clone();
	};
}

#endif //CORE_ENTITY_COMPONENT_DRAWABLE_HPP
