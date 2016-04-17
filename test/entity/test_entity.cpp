#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "entity/entity.hpp"
#include "common/logger.hpp"
#include "component/transform.hpp"

namespace game{

	const lest::test entity[] = {
		SCENARIO("It should create new entity ids"){

			GIVEN("an available entity facade"){

				WHEN("an entity is requested"){
					unsigned long id = Entity::Create();

					THEN("entity id should be stricly greater than zero"){
						EXPECT(id != 0);
					}
				}
				WHEN("an entity is destroyed and a new one is requested"){
					unsigned long id = Entity::Create();
					unsigned long expected_id = id;
					Entity::Destroy(id);
					id = Entity::Create();

					THEN("it should reuse the unused id"){
						EXPECT(id == expected_id);
					}
				}
			}
		},
		SCENARIO("It should register and retrieve components associated with id"){

			GIVEN("a valid and empty entity"){
				unsigned long id = Entity::Create();

				WHEN("a component is added to the entity"){
					Transform *transform = new Transform();
					Entity::AddComponent<Transform>(id, transform);

					THEN("it should be possible to retrieve it"){
						Transform *retrieved = Entity::GetComponent<Transform>(id);
						EXPECT(retrieved == transform);
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), entity);
}
