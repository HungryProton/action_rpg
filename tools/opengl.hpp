#ifndef GAME_TOOLS_OPENGL_HPP
#define GAME_TOOLS_OPENGL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>

#ifndef BUFFER_OFFSET
	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

namespace game{
	void _check_gl_error(const char* file, int line);
}

#endif //GAME_TOOLS_OPENGL_HPP
