#include "sprite_customization.hpp"
#include "core/service/builder/game_object_builder.hpp"
#include "core/locator/locator.hpp"
#include "core/component/transform.hpp"
#include "core/component/constraint.hpp"

namespace game{

	SpriteCustomization::SpriteCustomization() : Component(){
		this->parts.clear();
		this->init_done = false;
	}

	SpriteCustomization::SpriteCustomization(GameObject* parent) : SpriteCustomization(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	SpriteCustomization::SpriteCustomization(SpriteCustomization* sc){
		for(auto part : sc->parts){
			int index = part.first;
			GameObject* gp = part.second->Clone();
			this->parts.insert(std::make_pair(index, gp));
		}
		this->init_done = false;
	}

	SpriteCustomization* SpriteCustomization::Clone(){
		return new SpriteCustomization(this);
	}

	void SpriteCustomization::AddPart(GameObject* part, int order){
		this->parts.insert(std::make_pair(order, part));
		this->parent->AttachChild(part);
	}

	void SpriteCustomization::AddPart(std::string resource_file, int order){
		GameObjectBuilder* builder = Locator::Get<GameObjectBuilder>();

		GameObject* part = builder->LoadAnimatedSprite(resource_file);
		Transform* part_transform = part->GetComponent<Transform>();
		Transform* parent_transform = this->parent->GetComponent<Transform>();
		part_transform->position = parent_transform->position;
		part_transform->position += glm::vec3(0.f, -0.04f*order, 0.02f*order); // ... find something else, please.

		Constraint* c = new Constraint(part);
		c->type = ConstraintType::KEEP_OFFSET;
		c->SetOffset(&(part_transform->position), &(parent_transform->position));

		this->parent->AttachChild(part);
	}

	void SpriteCustomization::Update(){
		// do stuff
	}
}
