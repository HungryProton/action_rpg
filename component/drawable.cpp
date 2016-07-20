#include "drawable.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	Drawable::Drawable(){
		this->vao = 0;
		this->shader = 0;
		this->draw_type = 0;
		this->vertex_amount = 0;
		this->offset = 0;
		this->alpha = 1.0;
		this->type = DrawableType::NONE;
	}
}
