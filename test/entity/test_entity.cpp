#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "entity/entity.hpp"
#include "common/logger.hpp"
#include "component/transform.hpp"
#include "component/shapes/box.hpp"

namespace game{

	const lest::test entity[] = {
		SCENARIO("It should create new entity ids"){

			GIVEN("an available entity facade"){

				WHEN("an entity is requested"){
					unsigned long id = Entity::Create();

					THEN("entity id should be stricly greater than zero"){
						EXPECT(id != 0);
					}
					Entity::Destroy(id);
				}
				WHEN("an entity is destroyed and a new one is requested"){
					unsigned long id = Entity::Create();
					unsigned long expected_id = id;
					Entity::Destroy(id);
					id = Entity::Create();

					THEN("it should reuse the unused id"){
						EXPECT(id == expected_id);
					}
					Entity::Destroy(id);
				}
			}
		},
		SCENARIO("It should register and retrieve components associated with id"){

			GIVEN("a valid and empty entity"){
				unsigned long id = Entity::Create();

				WHEN("a component is added to the entity"){
					Transform *transform = new Transform();
					Entity::AttachComponent<Transform>(id, transform);

					THEN("it should be possible to retrieve it"){
						Transform *retrieved = Entity::GetComponent<Transform>(id);
						EXPECT(retrieved == transform);
					}
				}
				Entity::Destroy(id);
			}
		},
		SCENARIO("It should destroy every component associated with id"){

			GIVEN("a registered entity with a few components"){
				unsigned long entity = Entity::Create();
				new Transform(entity);
				new Box(entity);

				WHEN("the entity is destroyed"){
					Entity::Destroy(entity);

					THEN("the components should be deleted"){
						EXPECT(Entity::GetComponent<Transform>(entity) == nullptr);
						EXPECT(Entity::GetComponent<Box>(entity) == nullptr);
					}
				}
				Entity::Destroy(entity);
			}
		},
		SCENARIO("It should clone an entity with all its component"){

			GIVEN("a registered entity with two components attached"){
				unsigned long entity = Entity::Create();
				Transform* original_t = new Transform(entity);
				Box* original_b = new Box(entity);

				WHEN("the entity is cloned"){
					unsigned long cloned_entity = Entity::Clone(entity);

					THEN("it should have cloned components and attached them to the new entity"){
						Transform* cloned_t = Entity::GetComponent<Transform>(cloned_entity);
						Box* cloned_b = Entity::GetComponent<Box>(cloned_entity);

						EXPECT(cloned_t != nullptr);
						EXPECT(cloned_b != nullptr);
						EXPECT(cloned_t != original_t);
						EXPECT(cloned_b != original_b);
					}
					Entity::Destroy(cloned_entity);
				}
				Entity::Destroy(entity);
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), entity);
}
