#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "entity/entity.hpp"
#include "system/physic/physic.hpp"
#include "component/transform.hpp"
#include "component/shapes/circle.hpp"
#include "component/shapes/box.hpp"

using lest::approx;

namespace game{

	const lest::test physic[] = {
		SCENARIO("Physic objects should collide between them"){

			GIVEN("two intersecting colliders with a circle shape"){

				unsigned long circle1 = Entity::Create();
				unsigned long circle2 = Entity::Create();

				Transform* t1 = new Transform(circle1);
				Transform* t2 = new Transform(circle2);
				Circle* c1 = new Circle(circle1);
				Circle* c2 = new Circle(circle2);
				Collider* collider1 = new Collider(circle1);
				Collider* collider2 = new Collider(circle2);

				collider1->shape_type = std::type_index(typeid(Circle));
				collider2->shape_type = std::type_index(typeid(Circle));
				c1->radius = 2.f;
				c2->radius = 2.f;
				t2->position.y = 3;	//Both circle collide with a penetration vector of (0, -1, 0)

				WHEN("collisions are resolved"){

					Physic physic;
					physic.Update();

					THEN("they should have moved appart"){
						EXPECT(t1->position.y == approx(-0.5f).epsilon(0.1f));
						EXPECT(t2->position.y == approx(3.5f).epsilon(0.1f));
					}
				}

				delete circle1;
				delete circle2;
			}
			GIVEN("two intersecting colliders with a box shape"){

				unsigned long box1 = Entity::Create();
				unsigned long box2 = Entity::Create();

				Transform* t1 = new Transform(box1);
				Transform* t2 = new Transform(box2);
				new Box(2.f, 2.f, box1);
				new Box(2.f, 2.f, box2);
				Collider* collider1 = new Collider(box1);
				Collider* collider2 = new Collider(box2);

				collider1->shape_type = std::type_index(typeid(Box));
				collider2->shape_type = std::type_index(typeid(Box));

				WHEN("collision occurs on the horizontal faces"){
					t2->position.y = 1.f;	//Both boxes collide with a penetration vector of (0, -1.f, 0)

					Physic physic;
					box1->Update();
					box2->Update();
					physic.Update();

					THEN("the boxes should have moved appart"){
						EXPECT(t1->position.y == approx(-0.5f).epsilon(0.1));
						EXPECT(t2->position.y == approx(1.5f).epsilon(0.1));
					}
				}
				WHEN("collision occurs on the vertical faces"){
					t2->position.x = 1.f;
					Physic physic;
					box1->Update();
					box2->Update();
					physic.Update();

					THEN("the boxes should have moved appart"){
						EXPECT(t1->position.x == approx(-0.5f).epsilon(0.1));
						EXPECT(t2->position.x == approx(1.5f).epsilon(0.1));
					}
				}

				delete box1;
				delete box2;
			}
			GIVEN("two intersecting colliders with a box and a circle shape"){

				unsigned long box = Entity::Create();
				unsigned long circle = Entity::Create();

				Transform* t1 = new Transform(box);
				Transform* t2 = new Transform(circle);
				Box* b1 = new Box(2.f, 2.f, box);
				Circle* c1 = new Circle(2.f, circle);
				Collider* collider1 = new Collider(box);
				Collider* collider2 = new Collider(circle);

				collider1->shape_type = std::type_index(typeid(Box));
				collider2->shape_type = std::type_index(typeid(Circle));

				WHEN("collision occurs"){
					t2->position.y = 2.f;	//Both boxes collide with a penetration vector of (0, -1.f, 0)

					Physic physic;
					box->Update();
					circle->Update();
					physic.Update();

					THEN("the two objects should have moved appart"){
						EXPECT(t1->position.y == approx(-0.5f).epsilon(0.1));
						EXPECT(t2->position.y == approx(2.5f).epsilon(0.1));
					}
				}
				WHEN("collision occurs because the circle is inside the box"){
					b1->height = 6.f;
					b1->height = 6.f;
					c1->radius = 0.30f;
					t2->position.y = -2.f;

					Physic physic;
					box->Update();
					circle->Update();
					physic.Update();

					THEN("the two objects should have moved appart"){
						EXPECT(t1->position.y == approx(0.35f).epsilon(0.1));
						EXPECT(t2->position.y == approx(-2.65f).epsilon(0.1));
					}
				}
				delete box;
				delete circle;
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), physic);
}
