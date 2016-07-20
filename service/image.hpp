#ifndef GAME_IMAGE_HPP
#define GAME_IMAGE_HPP

#include "common/opengl.hpp"

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

