#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "service/shader_loader.hpp"
#include "test/context_util.hpp"

namespace game{

	const lest::test shader_loader[] = {

		SCENARIO("It should load shaders and return associated program id"){

			GIVEN("a ShaderLoader and a valid OpenGL context"){
				ContextUtil::CreateOpenGLContext();
				ShaderLoader loader;
				GLuint shader = 0;

				WHEN("a new shader is requested"){
					shader = loader.GetShader("shader/g_buffer.vs",
																		"shader/g_buffer.frag");

					THEN("it should return a valid shader program id"){
						EXPECT(shader != 0);
					}
					THEN("it should not produce any openGL error"){
						EXPECT(check_gl_error() == 0);
					}
				}
				WHEN("an invalid shader is requested"){
					shader = loader.GetShader("does/not/exists.vs", "does/not/exists.frag");
					THEN("the program id should be 0"){
						EXPECT(shader == 0);
					}
				}
				loader.ClearMemory();
				ContextUtil::DestroyOpenGLContext();
			}
		}

	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), shader_loader);
}
