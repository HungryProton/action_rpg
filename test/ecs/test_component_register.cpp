#include <iostream>
#include "deps/catch.hpp"
#include "ecs/ecs.hpp"

namespace game{

	// An empty component and a component with specialized constructor
	struct A{};
	struct B{
		int width = 0;
		int height = 0;
		B(int w, int h){
			width = w;
			height = h;
		}
	};

	SCENARIO("The registers should handle components operations on entities"){

		GIVEN("an empty entity"){
			Entity e = ecs::CreateEntity();

			WHEN("a component is attached to the entity"){
				// Create a component A and attach it to the entity
				A* component = ecs::CreateComponent<A>(e);

				THEN("it should be possible to retrieve the component"){
					// Get component of type A from entity e
					A* component2 = ecs::GetComponent<A>(e);
					REQUIRE_FALSE(component2 == nullptr);
					REQUIRE(component == component2);
				}
				AND_WHEN("we try to attach another component of same type to the entity"){
					A* component3 = ecs::CreateComponent<A>(e);

					THEN("it should not create a component but return the previously created one"){
						REQUIRE_FALSE(component3 == nullptr);
						REQUIRE(component3 == component);
					}
				}
			}
			WHEN("a component request to know the parent entity"){
				A* component = ecs::CreateComponent<A>(e);
				Entity e2 = ecs::GetParentOf(component);

				THEN("it should return the parent entity"){
					REQUIRE_FALSE(e.uid == 0);
					REQUIRE(e.uid == e2.uid);
				}
			}
			WHEN("a component is created with additional parameters"){
				B* b = ecs::CreateComponent<B>(e, 10, 25);

				THEN("these parameters should be passed to the component constructor"){
					REQUIRE_FALSE(b == nullptr);
					REQUIRE(b->width == 10);
					REQUIRE(b->height == 25);
				}
			}
		}
	}
}
