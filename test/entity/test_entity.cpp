#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "entity/entity.hpp"
#include "common/logger.hpp"

namespace game{

	const lest::test entity[] = {
		SCENARIO("It should create new entity ids"){

			GIVEN("an entity facade"){
				Entity entity_facade;

				WHEN("an entity is requested"){
					unsigned long id = entity_facade.Create();

					THEN("entity id should be stricly greater than zero"){
						EXPECT(id != 0);
					}
				}
				WHEN("an entity is destroyed and a new one is requested"){
					unsigned long id = entity_facade.Create();
					unsigned long expected_id = id;
					entity_facade.Destroy(id);
					id = entity_facade.Create();

					THEN("it should reuse the unused id"){
						EXPECT(id == expected_id);
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), entity);
}
