#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/opengl.hpp"
#include "test/context_util.hpp"

namespace game{

	const lest::test opengl[] = {

		SCENARIO("The check_gl_error should tell if an opengl error occured"){

			GIVEN("an initialized opengl context"){
				ContextUtil::CreateOpenGLContext();
				check_gl_error();	// Throw away eventual errors which happened before
													// the tests
				WHEN("A valid operation is performed"){
					GLuint vertexArray;
					glGenVertexArrays(1, &vertexArray);

					THEN("it should return 0"){
						EXPECT(check_gl_error() == 0);
					}
					glDeleteVertexArrays(1, &vertexArray);
				}
				WHEN("an invalid action is performed"){
					glBindBuffer(GL_ARRAY_BUFFER, 1442);

					THEN("it should return 1"){
						EXPECT(check_gl_error() == 1);
					}
				}

				ContextUtil::DestroyOpenGLContext();
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), opengl);
}
