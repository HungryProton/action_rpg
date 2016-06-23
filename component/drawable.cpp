#include "drawable.hpp"
#include "messaging/message_bus.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "ecs/entity.hpp"

namespace game{

	Drawable::Drawable() : Component(){
		this->vao = 0;
		this->shader = 0;
		this->draw_type = 0;
		this->vertex_amount = 0;
		this->offset = 0;
		this->alpha = 1.0;
		this->type = DrawableType::NONE;
	}

	Drawable::~Drawable(){ }

	Drawable::Drawable(unsigned long entity) : Drawable(){
		Entity::AttachComponent<Drawable>(entity, this);
	}

	Drawable::Drawable(Drawable* drawable){
		this->vao = drawable->vao;
		this->shader = drawable->shader;
		this->draw_type = drawable->draw_type;
		this->vertex_amount = drawable->vertex_amount;
		this->offset = drawable->offset;
		this->alpha = drawable->alpha;
	}

	Drawable* Drawable::Clone(){
		return new Drawable(this);
	}
}
