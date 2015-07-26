#include <cstdlib>
#include <iostream>
#include <string>
#include "core/services/render/render.hpp"
#include "core/locator/locator.hpp"
#include "texture.hpp"

namespace game{

    Texture::Texture(){
        this->texture = 0;
        this->width = 0;
        this->height = 0;
        this->transparent = false;
    }

    Texture::Texture(std::string file_path) : Texture(){
        Image *img = Locator::Get<ImageHelper>()->LoadFromFile(file_path);  
        if(!img){
            std::cerr << "Loading texture " << file_path << " failed" << std::endl;
            return;
        }
        this->texture = img->GL_texture;
        this->width = img->width;
        this->height = img->height; 
        this->transparent = false;
    }

    void Texture::Bind(GLenum active_texture = GL_TEXTURE0){
        glActiveTexture(active_texture);
        glBindTexture( GL_TEXTURE_2D, this->texture);
    }

    bool Texture::IsValid(){
        return this->texture != 0;
    }
}

