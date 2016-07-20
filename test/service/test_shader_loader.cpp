#include <iostream>
#include "deps/catch.hpp"
#include "service/shader_loader.hpp"
#include "test/context_util.hpp"

namespace game{

	SCENARIO("It should load shaders and return associated program id"){

		GIVEN("a ShaderLoader and a valid OpenGL context"){
			ContextUtil::CreateOpenGLContext();
			ShaderLoader loader;
			GLuint shader = 0;

			WHEN("a new shader is requested"){
				shader = loader.GetShader("shader/g_buffer.vs",
																	"shader/g_buffer.frag");

				THEN("it should return a valid shader program id"){
					REQUIRE(shader != 0);
				}
				THEN("it should not produce any openGL error"){
					REQUIRE(check_gl_error() == 0);
				}
			}
			WHEN("an invalid shader is requested"){
				shader = loader.GetShader("does/not/exists.vs", "does/not/exists.frag");
				THEN("the program id should be 0"){
					REQUIRE(shader == 0);
				}
			}
			loader.ClearMemory();
			ContextUtil::DestroyOpenGLContext();
		}
	}
}
