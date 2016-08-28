#include "atlas.hpp"
#include <fstream>
#include <sstream>
#include "common/logger.hpp"
#include "common/time.hpp"
#include "texture.hpp"

namespace game{

	Atlas::Atlas(){
		current_frame = 0;
		start_time = Time::GetCurrentTime();
		loop = true;
		play = true;
		current_direction = Direction::S;
	}

	Atlas::Atlas(std::string file_path) : Atlas(){
		LoadFromFile(file_path);
	}

	void Atlas::LoadFromFile(std::string file_path){
		base_name = file_path;
		std::string animation_name;
		std::string animation_path;
		int priority;

		std::ifstream file(file_path);
		if(file.is_open()){
			std::string folder_path = file_path.substr(0, file_path.find_last_of('/') + 1);
			while(file >> animation_name >> animation_path >> priority){
				this->LoadSpriteSheet(animation_name, folder_path + animation_path, priority);
			}
			file.close();
		}
		current_animation = animations.begin()->second;
	}

	void Atlas::LoadSpriteSheet(std::string name, std::string path, int priority){
		std::ifstream file(path + ".txt");
		if(!file.is_open()){ return; }

		Animation animation;
		animation.texture = new Texture(path + ".png");
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
					x /= animation.texture->width;
					y /= animation.texture->height;
					current_positions->push_back(glm::vec2(x, y));
				} else if (id == "size:"){
					int sx, sy;
					char c;
					iss >> sx >> c >> sy;
					// change this line to handle multiple sized glyphs
					animation.frame_size = glm::vec2(sx, sy);
				} else if (id == "index:"){
					reading_block = false;
				}
				continue;
			}

			if(!(iss >> current_angle)){ continue; }

			if(current_angle != previous_angle){
				Direction direction = GetDirectionFromAngle(current_angle);
				animation.positions.insert( std::make_pair(
																		direction,
																		std::vector<glm::vec2>()));
				current_positions = &(animation.positions.find(direction)->second);
				previous_angle = current_angle;
			}
			reading_block = true;
		}

		animation.frame_count = current_positions->size();
		animation.texture->ratio = glm::vec2( animation.frame_size.x / animation.texture->width,
				animation.frame_size.y / animation.texture->height);
		animation.texture->local_scale = glm::vec3(animation.frame_size.x / TEX_RATIO,
				animation.frame_size.y / TEX_RATIO,
				animation.frame_size.y / TEX_RATIO);
		animations.insert(std::make_pair(name, animation));

	}

	Direction Atlas::GetDirectionFromAngle(int angle){
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
