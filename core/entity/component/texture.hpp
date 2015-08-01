#ifndef GAME_COMPONENT_TEXTURE_HPP
#define GAME_COMPONENT_TEXTURE_HPP

#include <string>
#include "tools/opengl.hpp"
#include "core/entity/component/component.hpp"

namespace game{

    struct Texture : public Component{ 

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

