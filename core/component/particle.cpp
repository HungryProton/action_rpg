#include "particle.hpp"
#include "tools/time.hpp"
#include <algorithm>

namespace game{

	Particle::Particle() : Component(){
		this->life = 0.f;
		this->transform = nullptr;
		this->drawable = nullptr;
	}

	Particle::Particle(GameObject* parent) : Particle(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Particle::Particle(Particle* particle){
		this->life = particle->life;
		this->transform = nullptr;
		this->drawable = nullptr;
	}

	Particle::~Particle(){

	}

	Particle* Particle::Clone(){
		return new Particle(this);
	}

	void Particle::Update(){
		if( !this->IsAlive() || !this->drawable || !this->transform){ return; }
		float delta = Time::GetDeltaTime();

		life = std::max(0.f, life - delta);
		this->drawable->alpha = life;
		glm::vec3 target_velocity = this->transform->target_velocity;
		this->transform->position += target_velocity * delta;
	}

	bool Particle::IsAlive(){
		return this->life > 0;
	}

	void Particle::NotifyNewComponentAdded(){
		if(!this->parent){ return; }

		if(!this->transform){
			this->transform = this->parent->GetComponent<Transform>();
		}
		if(!this->drawable){
			this->drawable = this->parent->GetComponent<Drawable>();
		}
	}
}
