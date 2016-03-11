#include "particle_emitter.hpp"
#include "particle.hpp"
#include "tools/random.hpp"

namespace game{

	ParticleEmitter::ParticleEmitter() : Component(){
		this->one_shot = false;
		this->min_size = 0.5f;
		this->max_size = 1.f;
		this->min_count = 10;
		this->max_count = 20;
		this->min_duration = 1;
		this->max_duration = 3;
		this->direction = glm::vec3(0.f, 0.f, 1.f);
		this->scattering = 1.0f;
		this->speed = 1;
		this->alive_particles = 0;
		this->particle = nullptr;
	}

	ParticleEmitter::ParticleEmitter(GameObject* parent) : ParticleEmitter(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	ParticleEmitter::ParticleEmitter(ParticleEmitter* pe){
		this->one_shot = pe->one_shot;
		this->min_size = pe->min_size;
		this->max_size = pe->max_size;
		this->min_count = pe->min_count;
		this->max_count = pe->max_count;
		this->min_duration = pe->min_duration;
		this->max_duration = pe->max_duration;
		this->direction = pe->direction;
		this->scattering = pe->scattering;
		this->speed = pe->speed;
		this->particle = pe->particle->Clone();
	}

	ParticleEmitter::~ParticleEmitter(){
		for(GameObject* p : this->particles){
			delete p;
		}
		delete this->particle;
	}

	ParticleEmitter* ParticleEmitter::Clone(){
		return new ParticleEmitter(this);
	}

	void ParticleEmitter::Update(){
		if(this->alive_particles < this->min_count){
			this->ResurrectParticle();
		}

		this->alive_particles = this->particles.size();
		for(GameObject* p : this->particles){
			p->Update();
			if(!p->GetComponent<Particle>()->IsAlive()){
				this->alive_particles--;
			}
		}
	}

	void ParticleEmitter::ResurrectParticle(){
		GameObject* dead_particle = nullptr;
		Particle* p_comp;

		for(GameObject* particle : this->particles){
			p_comp = particle->GetComponent<Particle>();
			if(!p_comp->IsAlive()){
				dead_particle = particle;
				break;
			}
		}

		if(!dead_particle){	// if no available particle
			dead_particle = this->particle->Clone();
			p_comp = dead_particle->GetComponent<Particle>();
			this->particles.push_back(dead_particle);
		}

		Transform* t = dead_particle->GetComponent<Transform>();

		p_comp->life = 1.f;
		p_comp->fade = 1.f/(Random::NextFloat(this->max_duration - this->min_duration) + this->min_duration);
		t->position = this->parent->GetComponent<Transform>()->position;
		t->target_velocity = glm::normalize(glm::vec3(scattering/2.f - Random::NextFloat(scattering)) + this->direction) * this->speed;
	}

	void ParticleEmitter::SetParticle(GameObject* p){
		if(!p->GetComponent<Particle>()) { return; }
		if(!p->GetComponent<Transform>()){ return; }

		if(this->particle){
			delete this->particle;
		}
		this->particle = p;
	}
}
