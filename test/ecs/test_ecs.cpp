#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"

namespace game{

	const lest::test ecs[] = {
		SCENARIO("ECS should allow creating complete entities recognized by the systems"){

			GIVEN("A valid signature AB and an entity with a component A attached"){
				Node::CreateSignature<A,B>();
				Entity e = ECS::CreateEntity();
				Component<A>::CreateForEntity(e);

				WHEN("The entity only has a A component"){

					THEN("The entity list matching the AB signature should be empty"){
						EXPECT(Node::GetEntitiesMatching<A,B>().empty());
					}
				}

				WHEN("Component B is attached to the entity"){
					Component<B>::CreateForEntity(e);

					THEN("Entity list matching AB signature should contain the entity"){
						EXPECT(!Node::GetEntitiesMatching<A,B>().empty())
					}
				}
			}
			GIVEN("A valid AB signature and an entity matching it"){

				WHEN("The A component is removed"){

					THEN("It should no longer appear in the entity list for the AB signature"){
						EXPECT(Node::GetEntitiesMatching<A,B>().empty())
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), ecs);
}
