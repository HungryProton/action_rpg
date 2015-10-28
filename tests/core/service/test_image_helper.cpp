#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/service/helper/image_helper.hpp"
#include "tests/common/common.hpp"

namespace game{

	const lest::test image_helper[] = {

		CASE("Should create a GL_texture ID upon new texture request"){

			Common::CreateOpenGLContext();

			ImageHelper helper;
			Image *img = helper.LoadFromFile("tests/resources/1.png");

			EXPECT( img != nullptr );
			EXPECT( img->GL_texture != 0 );

			helper.ClearMemory();

			Common::DestroyOpenGLContext();
		},

	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), image_helper);
}
