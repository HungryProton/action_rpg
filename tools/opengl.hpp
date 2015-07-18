#ifndef GAME_TOOLS_OPENGL_HPP
#define GAME_TOOLS_OPENGL_HPP
#define check_gl_error() OpenGL::CheckForErrors(__FILE__,__LINE__)
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace game{
    
    class OpenGL{ 
        public:
            static void Initialize();
            static bool CheckForErrors(const char *file, int line);
            static bool IsInitialized();
            static void SetInitialized(bool);
        private:
            static bool initialized_;
    };
}

#endif //GAME_TOOLS_OPENGL_HPP
