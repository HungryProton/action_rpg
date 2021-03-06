#include <iostream>
#include "opengl.hpp"

namespace game{

	int _check_gl_error(const char *file, int line) {
		GLenum err (glGetError());

		while(err!=GL_NO_ERROR) {
			std::string error;

			switch(err) {
				case GL_INVALID_OPERATION:	error="INVALID_OPERATION";	break;
				case GL_INVALID_ENUM:				error="INVALID_ENUM";				break;
				case GL_INVALID_VALUE:			error="INVALID_VALUE";			break;
				case GL_OUT_OF_MEMORY:			error="OUT_OF_MEMORY";			break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:	error="INVALID_FRAMEBUFFER_OPERATION";	break;
			}

			std::cout << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<std::endl;
			err=glGetError();
			return 1;	// Error occured
		}
		return 0;	// No error
	}

	glm::vec2 GetWindowSize(GLFWwindow* window){
		glm::ivec2 size;
		glfwGetWindowSize(window, &size.x, &size.y);
		return size;
	}
}
