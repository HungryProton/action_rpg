#include <fstream>
#include <sstream>
#include "animated_texture.hpp"

namespace game{

	AnimatedTexture::AnimatedTexture() : Component(){
	}

	AnimatedTexture::~AnimatedTexture(){

	}

	AnimatedTexture::AnimatedTexture(GameObject* parent) : AnimatedTexture(){
		if(parent){
			parent->AttachComponent(this);
		}
	}

	AnimatedTexture::AnimatedTexture(std::string file_path, GameObject* parent) : 
		AnimatedTexture(parent){

		this->base_name = file_path;
		std::ifstream file(file_path);
		std::string animation_name;
		std::string animation_path;

		if(file.is_open()){
			while(file >> animation_name >> animation_path){
				this->LoadSpriteSheet(animation_name, animation_path);
			}
			file.close();
		}
	}

	AnimatedTexture::AnimatedTexture(AnimatedTexture* texture){
		this->base_name = texture->base_name;
		this->animations = texture->animations;

		for(auto pair : texture->atlas){
			this->atlas.insert(std::make_pair(pair.first, pair.second->Clone()));
		}
	}

	AnimatedTexture* AnimatedTexture::Clone(){
		return new AnimatedTexture(this);
	}

	AnimatedTexture::AnimatedTexture(std::string file_path) : AnimatedTexture(file_path, nullptr){ }

	void AnimatedTexture::LoadSpriteSheet(std::string name, std::string path){
		std::ifstream file(path + ".txt");
		if(!file.is_open()){
			return;
		}
		Animation animation;

		std::string line;
		while(std::getline(file, line)){
			std::istringstream iss(line);
			int angle;
			if(!(iss >> angle)){
				continue;
			}

			std::vector<glm::vec2> positions;

			while(std::getline(file, line)){
				std::string id;
				std::istringstream ss(line);

				ss >> id;

				if(id == "xy:"){
					int x, y;
					char c; // To ignore the comma
					ss >> x >> c >> y;
					positions.push_back(glm::vec2(x, y));
				} else if (id == "size:"){
					int sx, sy;
					char c;
					ss >> sx >> c >> sy;
					animation.size = glm::vec2(sx, sy);
				} else if (id == "index:"){
					break;
				}
			}
			animation.position.insert(
					std::make_pair(GetDirectionFromAngle(angle), positions));
		}
		this->animations.insert(std::make_pair(name, animation));
		Texture* t = new Texture(path + ".png");
		this->atlas.insert(std::make_pair(name, t));
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
