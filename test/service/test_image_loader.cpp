#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "service/image_loader.hpp"
#include "test/context_util.hpp"

namespace game{

	const lest::test image_loader[] = {

		SCENARIO("ImageLoader should handle image loading on the fly"){

			GIVEN("an ImageLoader and a valid OpenGL context"){
				ContextUtil::CreateOpenGLContext();
				ImageLoader loader;

				WHEN("a new image is requested"){

					Image *img = loader.LoadFromFile("test/data/1.png");

					THEN("it should return a valid pointer to an image"){
						EXPECT(img != nullptr);
					}
					THEN("it should create a new GL_texture ID"){
						EXPECT(img->GL_texture != 0u);
					}
					THEN("return image should have the proper dimensions"){
						EXPECT(img->width == 100);
						EXPECT(img->height == 100);
					}
				}
				WHEN("an invalid image is requested"){

					Image *invalid_img = loader.LoadFromFile("file/does/not/exists.png");

					THEN("it should return a null pointer"){
						EXPECT(invalid_img == nullptr);
					}
				}

				loader.ClearMemory();
				ContextUtil::DestroyOpenGLContext();
			}
		}

	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), image_loader);
}
