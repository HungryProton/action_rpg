#ifndef GAME_CORE_COMPONENT_ANIMATED_TEXTURE_HPP
#define GAME_CORE_COMPONENT_ANIMATED_TEXTURE_HPP

#include <map>
#include "component.hpp"
#include "texture.hpp"
#include "tools/opengl.hpp"


namespace game{

	enum class Direction{N,S,E,W,NE,NW,SE,SW};

	struct Animation{
		int frame_count;
		glm::vec2 size;
		std::multimap<Direction, std::vector<glm::vec2>> position;
	};

	struct AnimatedTexture : public Component{

		std::string base_name;
		std::map<std::string, Texture*> atlas;
		std::map<std::string, Animation> animations;

		Direction direction;
		bool loop;
		bool play;


		AnimatedTexture();
		~AnimatedTexture();
		AnimatedTexture(std::string);
		AnimatedTexture(std::string, GameObject*);
		AnimatedTexture(GameObject*);
		AnimatedTexture(AnimatedTexture*);
		virtual AnimatedTexture* Clone();
		void LoadSpriteSheet(std::string, std::string);
		Direction GetDirectionFromAngle(int);

	};
}

#endif //GAME_CORE_COMPONENT_ANIMATED_TEXTURE_HPP
