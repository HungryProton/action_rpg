#ifndef GAME_COMPONENT_ATLAS_HPP_
#define GAME_COMPONENT_ATLAS_HPP_

#include <string>
#include <map>
#include <vector>
#include "common.hpp"
#include "texture.hpp"

namespace game{

	struct Animation{
		std::string name;
		int frame_count;
		glm::vec2 frame_size;
		std::multimap<Direction, std::vector<glm::vec2>> positions;
		int priority;		// the lower, the higher the priority
		Texture* texture;
	};

	struct Atlas{
		std::map<std::string, Animation> animations;
		std::string base_name;
		Animation* current_animation;
		int current_frame;
		float start_time;
		bool loop;
		bool play;
		Direction current_direction;
		Atlas* master;

		Atlas();
		Atlas(std::string);
		void LoadFromFile(std::string);
		void SynchronizeWith(Atlas*);

		protected:
			void LoadSpriteSheet(std::string, std::string, int);
			Direction GetDirectionFromAngle(int);
	};
}

#endif //GAME_COMPONENT_ATLAS_HPP_
