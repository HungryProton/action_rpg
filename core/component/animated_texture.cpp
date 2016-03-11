#include <fstream>
#include <sstream>
#include "tools/time.hpp"
#include "animated_texture.hpp"
#include "drawable.hpp"

namespace game{

	AnimatedTexture::AnimatedTexture() : Component(){
		this->play = false;
		this->current_direction = Direction::S;
		this->loop = false;
		this->previous_frame = -1;
		this->current_animation = "";
		this->current_priority = -1;
	}

	AnimatedTexture::~AnimatedTexture(){
		for(auto it : this->atlas){
			delete it.second;
		}
	}

	AnimatedTexture::AnimatedTexture(GameObject* parent) : AnimatedTexture(){
		if(parent){
			parent->AttachComponent(this);
			parent->RegisterToLocalBus((MessageHandler<AnimationCommand>*)this);
		}
	}

	AnimatedTexture::AnimatedTexture(std::string file_path, GameObject* parent) : 
		AnimatedTexture(parent){

		this->base_name = file_path;
		std::ifstream file(file_path);
		std::string animation_name;
		std::string animation_path;
		int priority;

		if(file.is_open()){
			std::string folder_path = file_path.substr(0, file_path.find_last_of('/') + 1);
			while(file >> animation_name >> animation_path >> priority){
				this->LoadSpriteSheet(animation_name, folder_path + animation_path, priority);
			}
			file.close();
		}
		this->local_scale = glm::vec3(this->animations.begin()->second.size.x/32.f,
						this->animations.begin()->second.size.y/32.f,
						this->animations.begin()->second.size.y/32.f);
	}

	AnimatedTexture::AnimatedTexture(AnimatedTexture* texture) : AnimatedTexture(){
		this->base_name = texture->base_name;
		this->animations = texture->animations;
		this->loop = texture->loop;
		this->play = texture->play;
		this->previous_frame = texture->previous_frame;
		this->current_direction = texture->current_direction;
		this->current_ratio = texture->current_ratio;
		this->local_scale = texture->local_scale;

		for(auto pair : texture->atlas){
			this->atlas.insert(std::make_pair(pair.first, pair.second->Clone()));
		}
	}

	AnimatedTexture* AnimatedTexture::Clone(){
		return new AnimatedTexture(this);
	}

	AnimatedTexture::AnimatedTexture(std::string file_path) : AnimatedTexture(file_path, nullptr){ }

	void AnimatedTexture::Update(){
		this->MessageHandler<AnimationCommand>::UpdateMessages();
		if(!play){ return; }

		auto it = this->animations.find(current_animation);
		if(it == this->animations.end()){ return; }

		int frame_count = it->second.frame_count;
		float elapsed_time = glfwGetTime() - this->start_time;
		int current_frame = ((int)(elapsed_time*24.f))%frame_count;

		if(current_frame == this->previous_frame){
			return;
		}
		this->previous_frame = current_frame;
		auto it2 = it->second.position.find(current_direction);

		this->shift = it2->second[current_frame];
	}

	void AnimatedTexture::Play(std::string animation_name, Direction d){

		// don't play the animation if it is already playing
		if( this->play && (this->current_animation == animation_name) ){
			if(d == Direction::LAST){ return; }
			if(d == current_direction){ return; }
		}

		auto it = this->animations.find(animation_name);
		if(it == this->animations.end()){ return; } // Animation not found

		// don't play the animation if it has a lower priority
		//if(it->second.priority >= this->current_priority
		//		&& this->current_priority != -1){ return; }

		if(d != Direction::LAST){
			this->current_direction = d;
		}
		this->current_animation = animation_name;
		this->current_priority = it->second.priority;
		this->start_time = glfwGetTime();
		glm::vec2 size = it->second.size;
		Texture* texture = this->atlas.find(animation_name)->second;
		this->current_ratio = glm::vec2(size.x/texture->width, size.y/texture->height);
		this->previous_frame = -1;
		this->play = true;
	}

	void AnimatedTexture::Pause(){
		this->play = false;
	}

	void AnimatedTexture::Stop(){
		this->Pause();
	}

	void AnimatedTexture::OnMessage(AnimationCommand message){
		switch(message.action){
			case AnimationAction::PLAY:
				this->Play(message.name, message.direction);
				break;
			case AnimationAction::PAUSE:
				this->Pause();
				break;
			case AnimationAction::STOP:
				this->Stop();
				break;
		}
	}

	void AnimatedTexture::LoadSpriteSheet(std::string name, std::string path, int priority){
		std::ifstream file(path + ".txt");
		if(!file.is_open()){ return; }

		Animation animation;
		Texture* texture = new Texture(path + ".png");
		this->atlas.insert(std::make_pair(name, texture));
		animation.priority = priority;

		std::string line;
		int current_angle = -1;
		int previous_angle = -1;
		bool reading_block = false;
		std::vector<glm::vec2>* current_positions;

		while(std::getline(file, line)){
			std::istringstream iss(line);

			if(reading_block){
				std::string id;
				iss >> id;

				if(id == "xy:"){
					float x, y;
					char c; // To ignore the comma
					iss >> x >> c >> y;
					x /= texture->width;
					y /= texture->height;
					current_positions->push_back(glm::vec2(x, y));
				} else if (id == "size:"){
					int sx, sy;
					char c;
					iss >> sx >> c >> sy;
					// change this line to handle multiple sized glyphs
					animation.size = glm::vec2(sx, sy);
				} else if (id == "index:"){
					reading_block = false;
				}
				continue;
			}

			if(!(iss >> current_angle)){ continue; }

			if(current_angle != previous_angle){
				Direction direction = GetDirectionFromAngle(current_angle);
				animation.position.insert( std::make_pair(
																		direction,
																		std::vector<glm::vec2>()));
				current_positions = &(animation.position.find(direction)->second);
				previous_angle = current_angle;
			}
			reading_block = true;
		}

		animation.frame_count = current_positions->size();
		this->animations.insert(std::make_pair(name, animation));
	}

	void AnimatedTexture::Bind(GLenum active_texture = GL_TEXTURE0){
		//LOG(DEBUG) << current_animation << " " << this->atlas.find(current_animation)->second->texture << std::endl;
		glActiveTexture(active_texture);
		glBindTexture( GL_TEXTURE_2D, this->atlas.find(current_animation)->second->texture);
	}

	Direction AnimatedTexture::GetDirectionFromAngle(int angle){
		switch(angle){
			case 0:
				return Direction::S;
			case 45:
				return Direction::SE;
			case 90:
				return Direction::E;
			case 135:
				return Direction::NE;
			case 180:
				return Direction::N;
			case 225:
				return Direction::NW;
			case 270:
				return Direction::W;
			case 315:
				return Direction::SW;
			default:
				return Direction::S;
		}
	}

}
