#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "ecs/ecs.hpp"
#include "common/logger.hpp"

namespace game{

	struct A{};
	struct B{};

	SCENARIO("ECS should allow creating complete entities automatically recognized by the systems"){

		GIVEN("A valid signature AB and an entity with a component A attached"){
			ecs::CreateSignature<A,B>();
			Entity e = ecs::CreateEntity();
			ecs::CreateComponentForEntity<A>(e);

			WHEN("The entity only has a A component"){

				THEN("The entity list matching the AB signature should be empty"){
					auto list = ecs::GetEntitiesWithComponents<A,B>();
					REQUIRE(list.empty());
				}
			}
			WHEN("Component B is attached to the entity"){
				ecs::CreateComponentForEntity<B>(e);

				THEN("Entity list matching AB signature should contain the entity"){
					auto list = ecs::GetEntitiesWithComponents<A,B>();
					REQUIRE_FALSE(list.empty());
					REQUIRE(list[0].uid == e.uid);
				}
				AND_WHEN("Component A is removed from the entity"){
					ecs::RemoveComponentFromEntity<A>(e);

					THEN("It should no longer appear in the entity list for the AB signature"){
						auto list = ecs::GetEntitiesWithComponents<A,B>();
						REQUIRE(list.empty());
					}
				}
			}
			ecs::ClearMemory();
		}
	}
}
