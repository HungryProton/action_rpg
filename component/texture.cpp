#include <cstdlib>
#include <iostream>
#include <string>
#include "texture.hpp"
#include "common/logger.hpp"
#include "entity/entity.hpp"
#include "service/service.hpp"
#include "service/image_loader.hpp"

namespace game{

	Texture::Texture() : Component(){
		this->texture = 0;
		this->width = 0;
		this->height = 0;
		this->transparent = false;
		this->local_scale = glm::vec3(1.f, 1.f, 1.f);
	}

	Texture::Texture(unsigned long parent) : Texture(){
		Entity::AttachComponent<Texture>(parent, this);
	}

	Texture::Texture(Texture* texture) : Texture(){
		this->texture = texture->texture;
		this->width = texture->width;
		this->height = texture->height;
		this->transparent = texture->transparent;
		this->local_scale = texture->local_scale;
	}

	Texture::Texture(std::string file_path, unsigned long parent) : Texture(parent){

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

	Texture* Texture::Clone(){
		return new Texture(this);
	}
}

