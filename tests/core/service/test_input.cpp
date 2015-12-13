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

		CASE( "Should send messages" ){
			Input inputService;
			DummyMessageHandler object;

			//inputService.RegisterListener( &object );
		},
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), input);
}
