#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "common/opengl.hpp"
#include "test/context_util.hpp"

namespace game{

	SCENARIO("The check_gl_error should tell if an opengl error occured"){

		GIVEN("an initialized opengl context"){
			ContextUtil::CreateOpenGLContext();
			check_gl_error();	// Throw away eventual errors which happened before
												// the tests
			WHEN("A valid operation is performed"){
				GLuint vertexArray;
				glGenVertexArrays(1, &vertexArray);

				THEN("it should return 0"){
					REQUIRE(check_gl_error() == 0);
				}
				glDeleteVertexArrays(1, &vertexArray);
			}
			WHEN("an invalid action is performed"){
				glBindBuffer(GL_ARRAY_BUFFER, 1442);

				THEN("it should return 1"){
					REQUIRE(check_gl_error() == 1);
				}
			}

			ContextUtil::DestroyOpenGLContext();
		}
	}
}
