#define STB_IMAGE_IMPLEMENTATION
#include "deps/stb_image.h"

#include <iostream>
#include "image_helper.hpp"
#include "tools/logger.hpp"

namespace game{

    ImageHelper::ImageHelper(){

    }

    ImageHelper::~ImageHelper(){
        this->ClearMemory();
    }

    void ImageHelper::ClearMemory(){
        auto it = this->images_.begin();
        while(it != this->images_.end()){
            Image* img = it->second;
            it++;
            stbi_image_free(img->data);
            delete img;
        }
        images_.clear();
    }

    Image* ImageHelper::LoadFromFile(std::string file_path){

        // If Image was already loaded, return if
        Image* i = this->GetAlreadyLoadedImage(file_path);
        if(i){
            return i;
        }

        // If the Image wasn't previously loaded, load it now
        i = new Image();
        i->data = stbi_load(file_path.c_str(),
                            &i->width,
                            &i->height,
                            &i->comp,
                            0);

        if( !i->data ){ // Loading failed
            LOG(WARNING) << "Cannot load file " << file_path << std::endl;
            return nullptr;
        }

        // Generates OpenGL buffer. This will be stored and passed to the
        // rendering service to fetch the texture
        glGenTextures(1, &i->GL_texture);

        glBindTexture(GL_TEXTURE_2D, i->GL_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            // Default format to RGB, but if 4 components are found instead
            // of 3, it is RGBA
            GLenum format = GL_RGB;
            if(i->comp == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         format,
                         i->width,
                         i->height,
                         0,
                         format,
                         GL_UNSIGNED_BYTE,
                         i->data);

        glBindTexture(GL_TEXTURE_2D, 0);

        //stbi_image_free(i.data);  // TODO : Looks weird but was like that
                                    // before, revert changes if anything is
                                    // broken

        // Store new image for future use
        this->images_.insert( std::pair<std::string, Image*>( file_path, i ) );
        return i;
    }

    // Check if an Image has already been loaded
    // If loaded, Return the Image, return nullptr if not.
    Image* ImageHelper::GetAlreadyLoadedImage(std::string file_path){
        auto it = this->images_.find(file_path);

        if(it != this->images_.end()){
            return it->second;
        }
        return nullptr;
    }
}

