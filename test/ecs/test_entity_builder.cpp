#include <iostream>
#include "deps/catch.hpp"
#include "ecs/entity/entity_builder.hpp"

namespace game{

	SCENARIO("It should create new entity ids"){

		GIVEN("an available and new entity builder"){
			EntityBuilder builder;

			WHEN("an entity is requested"){
				Entity e = builder.Create();

				THEN("entity id should be stricly greater than zero"){
					REQUIRE(e.uid != 0);
				}
				builder.NotifyDeletionOf(e);
			}
			WHEN("an entity is destroyed and a new one is requested"){
				Entity e1 = builder.Create();
				builder.NotifyDeletionOf(e1);
				Entity e2 = builder.Create();

				THEN("it should reuse the unused id"){
					REQUIRE(e2.uid == e1.uid);
				}
			}
		}
	}
}
