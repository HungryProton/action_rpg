#include "drawable.hpp"
#include "core/messaging/message_bus.hpp"
#include "core/messaging/concrete_messages/rendering_intent.hpp"

namespace game{

	Drawable::Drawable() : Component(){
		this->vao = 0;
		this->shader = 0;
		this->draw_type = 0;
		this->vertex_amount = 0;
		this->offset = 0;
		this->alpha = 1.0;
	}

	Drawable::Drawable(GameObject* parent) : Drawable(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Drawable::Drawable(Drawable* drawable){
		this->vao = drawable->vao;
		this->shader = drawable->shader;
		this->draw_type = drawable->draw_type;
		this->vertex_amount = drawable->vertex_amount;
		this->offset = drawable->offset;
		this->alpha = drawable->alpha;
		this->parent = nullptr;
		this->is_attached = false;
	}

	void Drawable::Update(){
		RenderingIntent intent;
		intent.action = RI_RENDER_DRAWABLE;
		intent.game_object = this->parent;
		MessageBus::Push(intent);
	}

	Drawable* Drawable::Clone(){
		return new Drawable(this);
	}
}
