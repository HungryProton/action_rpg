#ifndef GAME_IMAGE_HPP
#define GAME_IMAGE_HPP

#include "tools/opengl.hpp"

namespace game{

    struct Image{
        GLuint GL_texture;
        unsigned char* data;
        int width;
        int height;
        int comp;
    };
}

#endif //GAME_IMAGE_HPP

