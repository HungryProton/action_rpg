#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "common/logger.hpp"
#include "service/image_loader.hpp"
#include "service/buffer_allocator.hpp"
#include "service/locator/locator.hpp"

namespace game{

	SCENARIO("Service locator should provide access to registered services"){

		GIVEN("an service locator with a single service registered"){
			Locator locator;
			ImageLoader* img_service = new ImageLoader();

			locator.Transfer(img_service);

			WHEN("an existing service is requested"){
				ImageLoader* service = locator.Get<ImageLoader>();

				THEN("it should return a pointer to the proper service"){
					REQUIRE(service == img_service);
				}
			}
			WHEN("an unregistered service is requested"){
				BufferAllocator* allocator = locator.Get<BufferAllocator>();

				THEN("it should return a null pointer"){
					REQUIRE(allocator == nullptr);
				}
			}
			WHEN("locator's memory is cleared"){
				locator.ClearMemory();

				THEN("it should destroy registered services"){
					REQUIRE(locator.Get<ImageLoader>() == nullptr);
				}
			}
		}
	}
}
