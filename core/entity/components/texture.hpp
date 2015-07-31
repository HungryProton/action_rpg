#ifndef GAME_COMPONENT_TEXTURE_HPP
#define GAME_COMPONENT_TEXTURE_HPP

#include <string>
#include "tools/opengl.hpp"

namespace game{

    struct Texture{ 

        GLuint texture;
        int width;
        int height;
        bool transparent;

        // ---- Helper methods ---- //
        Texture();
        Texture(std::string);
        bool IsValid();
        void Bind(GLenum);
    };
}

#endif // GAME_COMPONENT_TEXTURE_HPP

