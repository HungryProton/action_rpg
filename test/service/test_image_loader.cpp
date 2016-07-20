#include <iostream>
#include "deps/catch.hpp"
#include "service/image_loader.hpp"
#include "test/context_util.hpp"

namespace game{

	SCENARIO("ImageLoader should handle image loading on the fly"){

		GIVEN("an ImageLoader and a valid OpenGL context"){
			ContextUtil::CreateOpenGLContext();
			ImageLoader loader;

			WHEN("a new image is requested"){

				Image *img = loader.LoadFromFile("test/data/1.png");

				THEN("it should return a valid pointer to an image"){
					REQUIRE(img != nullptr);
				}
				THEN("it should create a new GL_texture ID"){
					REQUIRE(img->GL_texture != 0u);
				}
				THEN("return image should have the proper dimensions"){
					REQUIRE(img->width == 100);
					REQUIRE(img->height == 100);
				}
			}
			WHEN("an invalid image is requested"){

				Image *invalid_img = loader.LoadFromFile("file/does/not/exists.png");

				THEN("it should return a null pointer"){
					REQUIRE(invalid_img == nullptr);
				}
			}

			loader.ClearMemory();
			ContextUtil::DestroyOpenGLContext();
		}
	}
}
