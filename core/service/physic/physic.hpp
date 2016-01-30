#ifndef GAME_SYSTEM_PHYSIC_HPP
#define GAME_SYSTEM_PHYSIC_HPP

#include <glm/glm.hpp>
#include "../service.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/component/collider.hpp"
#include "core/component/transform.hpp"

namespace game{

	class GameObject;
	struct Manifold;

	class Physic : public CoreService{
		public:
			Physic();
			~Physic();
			virtual void ClearMemory();
			virtual void Update();

			void SetProcessedState(bool);
			bool GetProcessedState();

		private:
			void Process();
			void ApplyForce(glm::vec3 force, GameObject*);

			void UpdatePositions();
			void ResolveCollisions();
			void BoxvsBox(GameObject*, GameObject*);
			void CirclevsCircle(GameObject*, GameObject*);
			void BoxvsCircle(GameObject*, GameObject*);
			void ApplyImpulse(Manifold);
			void ApplyFriction(Manifold);
			void PositionalCorrection(Manifold);

			std::vector<GameObject*> collider_pool_;
	};

	struct Manifold{
		Collider* collider_a;
		Collider* collider_b;
		Transform* transform_a;
		Transform* transform_b;
		float penetration;
		glm::vec3 normal;
	};
}

#endif // GAME_SYSTEM_PHYSIC_HPP
