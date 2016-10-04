#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "ecs/ecs.hpp"
#include "common/logger.hpp"

namespace game{

	struct A{};
	struct B{};
	struct C{};

	SCENARIO("Nodes should keep track of entities matching their signature"){

		GIVEN("A valid signature AB and an entity with a component A attached"){
			ecs::CreateSignature<A,B>();
			Entity e = ecs::CreateEntity();
			ecs::CreateComponent<A>(e);

			WHEN("The entity only has a A component"){

				THEN("The entity list matching the AB signature should be empty"){
					auto list = ecs::GetEntitiesWithComponents<A,B>();
					REQUIRE(list.empty());
				}
			}
			WHEN("Component B is attached to the entity"){
				ecs::CreateComponent<B>(e);

				THEN("Entity list matching AB signature should contain the entity"){
					auto list = ecs::GetEntitiesWithComponents<A,B>();
					REQUIRE_FALSE(list.empty());
					REQUIRE(list[0].uid == e.uid);
				}
				WHEN("Component C is added to the entity"){
					int list_size = ecs::GetEntitiesWithComponents<A,B>().size();
					ecs::CreateComponent<C>(e);

					THEN("The list shouldn't have changed"){
						int new_list_size = ecs::GetEntitiesWithComponents<A,B>().size();
						REQUIRE(new_list_size == list_size);
					}
				}
				WHEN("Component A is removed from the entity"){
					ecs::RemoveAllComponent<A>(e);

					THEN("It should no longer appear in the entity list for the AB signature"){
						auto list = ecs::GetEntitiesWithComponents<A,B>();
						REQUIRE(list.empty());
					}
				}
				WHEN("Entity is deleted"){
					ecs::DestroyEntity(e);
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
