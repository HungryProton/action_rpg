#ifndef GAME_CORE_COMPONENT_PARTICLE_HPP
#define GAME_CORE_COMPONENT_PARTICLE_HPP

#include "component.hpp"
#include "transform.hpp"
#include "drawable.hpp"

namespace game{

	struct Particle : public Component{
		float life;
		float fade;

		Particle();
		Particle(GameObject*);
		Particle(Particle*);
		~Particle();
		virtual Particle* Clone();
		virtual void Update();
		virtual void NotifyNewComponentAdded();
		bool IsAlive();

		private:
			Transform* transform;
			Drawable* drawable;
	};
}

#endif //GAME_CORE_COMPONENT_PARTICLE_HPP
