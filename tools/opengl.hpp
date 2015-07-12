#ifndef GAME_TOOLS_OPENGL_HPP
#define GAME_TOOLS_OPENGL_HPP
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace game{
     static bool _check_gl_error(const char *file, int line);
}

#endif //GAME_TOOLS_OPENGL_HPP
