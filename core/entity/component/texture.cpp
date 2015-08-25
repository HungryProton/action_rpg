#include <cstdlib>
#include <iostream>
#include <string>
#include "tools/logger.hpp"
#include "core/service/render/render.hpp"
#include "core/locator/locator.hpp"
#include "texture.hpp"
#include "core/game/game.hpp"

namespace game{

    Texture::Texture(){
        // Inform the game that this component needs the ImageHelper service
        Game::RequestForService<ImageHelper>();

        this->texture = 0;
        this->width = 0;
        this->height = 0;
        this->transparent = false;
    }

    Texture::Texture(std::string file_path) : Texture(){

        // Get the image helper that actually load images
        ImageHelper* image_helper = Locator::Get<ImageHelper>();
        if( !image_helper ){
            log(ERROR) << "ImageHelper service has not been loaded yet" << std::endl;
            return;
        }

        // Load the image
        Image *img = image_helper->LoadFromFile(file_path);  
        if(!img){
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
