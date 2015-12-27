#include <cstdlib>
#include "material.hpp"

namespace game{

	Material::Material(GameObject* p) : Component(p){
		this->friction = 1;
		this->inflamable_factor = 0;
		this->absorbion_factor = 0;
		this->restitution = 0;
		this->density = 1;
	}

	Material::Material(MaterialPreset preset, GameObject* p) : Material(p){
		this->UsePreset(preset);
	}

	Material::Material(Material* material){
		this->friction = material->friction;
		this->inflamable_factor = material->inflamable_factor;
		this->absorbion_factor = material->absorbion_factor;
		this->restitution = material->restitution;
		this->density = material->density;
		this->is_attached = false;
	}

	void Material::UsePreset(MaterialPreset p){
		switch(p){
			case WOOD:
				this->friction = 1.8;
				this->inflamable_factor = 1;
				this->absorbion_factor = 0.5;
				this->restitution = 0;
				this->density = 700;
				break;

			case METAL:
				this->friction = 1.3;
				this->inflamable_factor = 0;
				this->absorbion_factor = 0;
				this->restitution = 0;
				this->density = 4000;
				break;

			case CONCRETE:
				this->friction = 1.5;
				this->inflamable_factor = 0;
				this->absorbion_factor = 0.3;
				this->restitution = 0;
				this->density = 2000;
				break;

			case EARTH:
				this->friction = 1;
				this->inflamable_factor = 0;
				this->absorbion_factor = 1;
				this->restitution = 0;
				this->density = 1000;
				break;
		}
	}

	Material* Material::Clone(){
		return new Material(this);
	}
}
