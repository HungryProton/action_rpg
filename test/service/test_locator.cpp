#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/logger.hpp"
#include "service/image_loader.hpp"
#include "service/buffer_allocator.hpp"
#include "service/locator/locator.hpp"

namespace game{

	const lest::test locator[] = {

		SCENARIO("Service locator should provide access to registered services"){

			GIVEN("an service locator with a single service registered"){
				Locator locator;
				ImageLoader* img_service = new ImageLoader();

				locator.Transfer(img_service);

				WHEN("an existing service is requested"){
					ImageLoader* service = locator.Get<ImageLoader>();

					THEN("it should return a pointer to the proper service"){
						EXPECT(service == img_service);
					}
				}
				WHEN("an unregistered service is requested"){
					BufferAllocator* allocator = locator.Get<BufferAllocator>();

					THEN("it should return a null pointer"){
						EXPECT(allocator == nullptr);
					}
				}
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), locator);
}
