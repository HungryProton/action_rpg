#include <cstdlib>
#include <iostream>
#include <string>
#include "texture.hpp"
#include "common/logger.hpp"
#include "ecs/entity/entity.hpp"
#include "service/service.hpp"
#include "service/image_loader.hpp"

namespace game{

	Texture::Texture(){
		this->texture = 0;
		this->width = 0;
		this->height = 0;
		this->transparent = false;
		this->local_scale = glm::vec3(1.f, 1.f, 1.f);
	}

	Texture::Texture(std::string file_path){

		// Get the image helper that actually load images
		ImageLoader* image_loader = Service::Get<ImageLoader>();

		// Load the image
		Image *img = image_loader->LoadFromFile(file_path);
		if(!img){ return; }

		this->texture = img->GL_texture;
		this->width = img->width;
		this->height = img->height;
		this->transparent = false;
		this->local_scale = glm::vec3(this->width/32.f, this->height/32.f, this->height/32.f);
	}

	void Texture::Bind(GLenum active_texture = GL_TEXTURE0){
		glActiveTexture(active_texture);
		glBindTexture( GL_TEXTURE_2D, this->texture);
	}

	bool Texture::IsValid(){
		return this->texture != 0;
	}
}

