#ifndef GAME_SYSTEM_PHYSIC_HPP
#define GAME_SYSTEM_PHYSIC_HPP

#include <glm/glm.hpp>
#include "../system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/physic_intent.hpp"
#include "component/collider.hpp"
#include "component/transform.hpp"
#include "component/shapes/shape.hpp"

namespace game{

	struct PhysicManifold;
	struct PhysicComponents;

	class Physic : public System,
								 public MessageHandler<PhysicIntent>{
		public:
			Physic();
			~Physic();

		protected:
			virtual void BeforeUpdate();
			virtual void OnUpdate(unsigned long);
			virtual void OnMessage(PhysicIntent);

		private:
			void ApplyForce(glm::vec3 force, unsigned long);

			void UpdatePositions(PhysicComponents*);
			void ResolveCollisions(unsigned long, PhysicComponents*);
			void BoxvsBox(PhysicComponents*, PhysicComponents*);
			void CirclevsCircle(PhysicComponents*, PhysicComponents*);
			void BoxvsCircle(PhysicComponents*, PhysicComponents*);
			void ApplyImpulse(PhysicManifold);
			void ApplyFriction(PhysicManifold);
			void PositionalCorrection(PhysicManifold);
			PhysicComponents* GetComponentsFor(unsigned long);

			std::map<unsigned long, PhysicComponents> entities_;
	};

	struct PhysicComponents{
		Collider* collider;
		Transform* transform;
		ShapeComponent* shape;
	};

	struct PhysicManifold{
		Collider* collider_a;
		Collider* collider_b;
		Transform* transform_a;
		Transform* transform_b;
		float penetration;
		glm::vec3 normal;
	};
}

#endif // GAME_SYSTEM_PHYSIC_HPP
