#ifndef GAME_CORE_COMPONENT_PARTICLE_EMITTER_HPP
#define GAME_CORE_COMPONENT_PARTICLE_EMITTER_HPP

#include "component.hpp"
#include "tools/glm.hpp"

namespace game{

	struct ParticleEmitter : public Component{
		bool one_shot;
		float min_size;
		float max_size;
		float min_count;
		float max_count;
		float min_life;
		float max_life;
		glm::vec3 direction;
		float scattering;
		float speed; //in m/s

		// Helpers
		ParticleEmitter();
		ParticleEmitter(GameObject*);
		ParticleEmitter(ParticleEmitter*);
		~ParticleEmitter();
		virtual ParticleEmitter* Clone();

		void Update();
		void CreateParticleFromImage(std::string);
		void SetParticle(GameObject*);

		private:
			std::vector<GameObject*> particles;
			GameObject* particle;
			int alive_particles;

			void ResurrectParticle();
	};
}
#endif //GAME_CORE_COMPONENT_PARTICLE_EMITTER_HPP
