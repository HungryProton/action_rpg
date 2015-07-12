#include <iostream>
#include "opengl.hpp"

namespace game{

     bool _check_gl_error(const char *file, int line) {
        GLenum err (glGetError());
        bool error_occured = false; 

        while(err!=GL_NO_ERROR) {
            error_occured = true;
            std::string error;

            switch(err) {
                case GL_INVALID_OPERATION:      
                    error="INVALID_OPERATION"; 
                    break;
                case GL_INVALID_ENUM:
                    error="INVALID_ENUM"; 
                    break;
                case GL_INVALID_VALUE:
                    error="INVALID_VALUE";          
                    break;
                case GL_OUT_OF_MEMORY:
                    error="OUT_OF_MEMORY";          
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error="INVALID_FRAMEBUFFER_OPERATION";
                    break;
                default:
                    error="UNHANDLED_ERROR" + err;
            }

            std::cout << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<std::endl;
            err=glGetError();
        }

        return error_occured;
    }
}
