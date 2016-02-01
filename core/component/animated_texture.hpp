#ifndef GAME_CORE_COMPONENT_ANIMATED_TEXTURE_HPP
#define GAME_CORE_COMPONENT_ANIMATED_TEXTURE_HPP

#include <map>
#include "component.hpp"
#include "common.hpp"
#include "texture.hpp"
#include "tools/opengl.hpp"
#include "core/messaging/concrete_messages/animation_command.hpp"
#include "core/messaging/message_handler.hpp"

namespace game{

	struct Animation{
		int frame_count;
		glm::vec2 size;
		std::multimap<Direction, std::vector<glm::vec2>> position;
	};

	struct AnimatedTexture : public Component, public MessageHandler<AnimationCommand>{

		std::string base_name;
		std::map<std::string, Texture*> atlas;
		std::map<std::string, Animation> animations;

		bool loop;
		bool play;
		float start_time;
		std::string current_animation;
		Direction current_direction;
		glm::vec2 current_ratio; // Updated when animation change
		int previous_frame;
		glm::vec2 shift;
		glm::vec3 local_scale;

		AnimatedTexture();
		~AnimatedTexture();
		AnimatedTexture(std::string);
		AnimatedTexture(std::string, GameObject*);
		AnimatedTexture(GameObject*);
		AnimatedTexture(AnimatedTexture*);
		virtual AnimatedTexture* Clone();
		virtual void Update();
		void Play(std::string, Direction);
		void Pause();
		void Stop();
		void Bind(GLenum);

		void LoadSpriteSheet(std::string, std::string);
		Direction GetDirectionFromAngle(int);
		void ProcessReceivedMessages();
	};
}

#endif //GAME_CORE_COMPONENT_ANIMATED_TEXTURE_HPP
