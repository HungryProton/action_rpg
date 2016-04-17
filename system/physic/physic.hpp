#ifndef GAME_SYSTEM_PHYSIC_HPP
#define GAME_SYSTEM_PHYSIC_HPP

#include <glm/glm.hpp>
#include "../system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/physic_intent.hpp"
#include "component/collider.hpp"
#include "component/transform.hpp"

namespace game{

	class GameObject;
	struct Manifold;
	struct PhysicComponents;

	class Physic : public System,
								 public MessageHandler<PhysicIntent>{
		public:
			~Physic();
			virtual void AssociateEntity(unsigned long);
			virtual void Update();

		private:
			void ApplyForce(glm::vec3 force, unsigned long);

			void UpdatePositions();
			void ResolveCollisions();
			void BoxvsBox(unsigned long, unsigned long);
			void CirclevsCircle(unsigned long, unsigned long);
			void BoxvsCircle(unsigned long, unsigned long);
			void ApplyImpulse(Manifold);
			void ApplyFriction(Manifold);
			void PositionalCorrection(Manifold);
			virtual void OnMessage(PhysicIntent);

			std::vector<unsigned long> collider_pool_;
			std::map<unsigned long, PhysicComponents> entities_;
	};

	struct PhysicComponents{
		Collider* collider;
		Transform* transform;
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
