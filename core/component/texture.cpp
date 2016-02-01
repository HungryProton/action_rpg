#include <cstdlib>
#include <iostream>
#include <string>
#include "tools/logger.hpp"
#include "core/service/render/render.hpp"
#include "core/service/helper/image_helper.hpp"
#include "core/locator/locator.hpp"
#include "texture.hpp"
#include "core/game/game.hpp"

namespace game{

	Texture::Texture() : Component(){
		this->texture = 0;
		this->width = 0;
		this->height = 0;
		this->transparent = false;
		this->local_scale = glm::vec3(1.f, 1.f, 1.f);

		// Inform the game that this component needs the ImageHelper service
		Game::RequestForService<ImageHelper>();
	}

	Texture::Texture(GameObject* parent) : Texture(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	Texture::Texture(Texture* texture) : Texture(){
		this->texture = texture->texture;
		this->width = texture->width;
		this->height = texture->height;
		this->transparent = texture->transparent;
		this->local_scale = texture->local_scale;
		this->is_attached = false;
	}

	Texture::Texture(std::string file_path, GameObject* parent) : Texture(parent){

		// Get the image helper that actually load images
		ImageHelper* image_helper = Locator::Get<ImageHelper>();
		if( !image_helper ){
				LOG(ERROR) << "ImageHelper service has not been loaded yet" << std::endl;
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

