#include "deps/catch.hpp"
#include "ecs/ecs.hpp"
#include "system/physic/physic.hpp"
#include "component/transform.hpp"
#include "component/shapes/circle.hpp"
#include "component/shapes/box.hpp"
#include "messaging/concrete_messages/physic_intent.hpp"
#include "common/time.hpp"

namespace game{

	SCENARIO("Physic objects should collide between them"){

		GIVEN("two intersecting colliders with a circle shape"){
			Physic physic_system;
			Entity circle1 = ecs::CreateEntity();
			Entity circle2 = ecs::CreateEntity();

			Transform* t1 = ecs::CreateComponent<Transform>(circle1);
			Transform* t2 = ecs::CreateComponent<Transform>(circle2);
			Circle* c1 = ecs::CreateComponent<Circle>(circle1);
			Circle* c2 = ecs::CreateComponent<Circle>(circle2);
			Collider* collider1 = ecs::CreateComponent<Collider>(circle1);
			Collider* collider2 = ecs::CreateComponent<Collider>(circle2);

			collider1->shape_type = Shape::CIRCLE;
			collider2->shape_type = Shape::CIRCLE;
			c1->radius = 2.f;
			c2->radius = 2.f;
			t2->position.y = 3;	//Both circle collides with a penetration vector of (0, -1, 0)

			WHEN("collisions are resolved"){
				physic_system.Update();

				THEN("they should have moved appart"){
					REQUIRE(t1->position.y == Approx(-0.5f).epsilon(0.1f));
					REQUIRE(t2->position.y == Approx(3.5f).epsilon(0.1f));
				}
			}
			ecs::DestroyEntity(circle1);
			ecs::DestroyEntity(circle2);
		}
		GIVEN("two intersecting colliders with a box shape"){
			Physic physic_system;
			Entity box1 = ecs::CreateEntity();
			Entity box2 = ecs::CreateEntity();

			Transform* t1 = ecs::CreateComponent<Transform>(box1);
			Transform* t2 = ecs::CreateComponent<Transform>(box2);
			ecs::CreateComponent<Box>(box1, 2.f, 2.f);
			ecs::CreateComponent<Box>(box2, 2.f, 2.f);
			Collider* collider1 = ecs::CreateComponent<Collider>(box1);
			Collider* collider2 = ecs::CreateComponent<Collider>(box2);

			collider1->shape_type = Shape::BOX;
			collider2->shape_type = Shape::BOX;

			WHEN("collision occurs on the horizontal faces"){
				t2->position.y = 1.f;	//Both boxes collide with a penetration vector of (0, -1.f, 0)

				physic_system.Update();

				THEN("the boxes should have moved appart"){
					REQUIRE(t1->position.y == Approx(-0.5f).epsilon(0.1));
					REQUIRE(t2->position.y == Approx(1.5f).epsilon(0.1));
				}
			}
			WHEN("collision occurs on the vertical faces"){
				t2->position.x = 1.f;
				physic_system.Update();

				THEN("the boxes should have moved appart"){
					REQUIRE(t1->position.x == Approx(-0.5f).epsilon(0.1));
					REQUIRE(t2->position.x == Approx(1.5f).epsilon(0.1));
				}
			}
			ecs::DestroyEntity(box1);
			ecs::DestroyEntity(box2);
		}
		GIVEN("two intersecting colliders with a box and a circle shape"){
			Physic physic_system;
			Entity box = ecs::CreateEntity();
			Entity circle = ecs::CreateEntity();

			Transform* t1 = ecs::CreateComponent<Transform>(box);
			Transform* t2 = ecs::CreateComponent<Transform>(circle);
			Box* b1 = ecs::CreateComponent<Box>(box, 2.f, 2.f);
			Circle* c1 = ecs::CreateComponent<Circle>(circle, 2.f);
			Collider* collider1 = ecs::CreateComponent<Collider>(box);
			Collider* collider2 = ecs::CreateComponent<Collider>(circle);

			collider1->shape_type = Shape::BOX;
			collider2->shape_type = Shape::CIRCLE;

			WHEN("collision occurs"){
				t2->position.y = 2.f;	//Both boxes collide with a penetration vector of (0, -1.f, 0)
				physic_system.Update();

				THEN("the two objects should have moved appart"){
					REQUIRE(t1->position.y == Approx(-0.5f).epsilon(0.1));
					REQUIRE(t2->position.y == Approx(2.5f).epsilon(0.1));
				}
			}
			WHEN("the order is reversed (circle -> box)"){
				ecs::RemoveAllComponent<Box>(box);
				b1 = ecs::CreateComponent<Box>(box, 2.f, 2.f);

				t2->position.y = 2.f;
				physic_system.Update();

				THEN("it should behave exactly the same way"){
					REQUIRE(t1->position.y == Approx(-0.5f).epsilon(0.1));
					REQUIRE(t2->position.y == Approx(2.5f).epsilon(0.1));
				}
			}
			WHEN("collision occurs because the circle is inside the box"){
				b1->height = 6.f;
				b1->height = 6.f;
				c1->radius = 0.30f;
				t2->position.y = -2.f;

				physic_system.Update();

				THEN("the two objects should have moved appart"){
					REQUIRE(t1->position.y == Approx(0.35f).epsilon(0.1));
					REQUIRE(t2->position.y == Approx(-2.65f).epsilon(0.1));
				}
			}
			ecs::DestroyEntity(box);
			ecs::DestroyEntity(circle);
		}
	}
	SCENARIO("Forces can be applied on physic objects"){

		GIVEN("a physical object alone"){
			Physic physic_system;
			Entity box = ecs::CreateEntity();

			Transform* t = ecs::CreateComponent<Transform>(box);
			ecs::CreateComponent<Box>(box, 2.f, 2.f);
			Collider* c = ecs::CreateComponent<Collider>(box);
			c->shape_type = Shape::BOX;

			WHEN("a force is applied on it"){
				PhysicIntent msg;
				msg.action = PhysicAction::APPLY_FORCE;
				msg.dest = box;
				msg.force = glm::vec3(2000, 0, 0);	// force in newtons in each axis
				MessageBus::Push(msg);

				physic_system.Update();

				THEN("it the object should have been moved"){
					REQUIRE(t->position.x > 0);
				}
			}
		}
	}
}
