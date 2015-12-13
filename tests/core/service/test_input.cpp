#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "core/service/input/input.hpp"

namespace game{

	class DummyMessageHandler{
		public:
			bool received;
	};

	const lest::test input[] = {
		SCENARIO("Input service should generate InputMessages on player input"){

			GIVEN("a running input service and an InputMessage handler"){

				WHEN("a player presses a key"){

					THEN("it should emit a KeyPressed InputMessage"){

					}
					THEN("the handler should receive a KeyPressed InputMessage"){

					}
				}

				WHEN("a player releases a key"){

					THEN("it should emit a KeyReleased InputMessage"){

					}
					THEN("the handler should receive a KeyReleased message"){

					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), input);
}
