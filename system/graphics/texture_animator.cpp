#include "texture_animator.hpp"
#include "component/atlas.hpp"
#include "common/time.hpp"

namespace game{

	TextureAnimator::TextureAnimator() : System(){
		Require<Atlas>();
	}

	TextureAnimator::~TextureAnimator(){ }

	void TextureAnimator::BeforeUpdate(){
		this->MessageHandler<AnimationCommand>::PollMessages();
	}

	void TextureAnimator::OnUpdate(Entity e){
		Atlas* atlas = ecs::GetComponent<Atlas>(e);

		float current_time = Time::GetCurrentTime();
		float elapsed_time = current_time - atlas->start_time;
		int current_frame = (int)(elapsed_time*24.f);
		if(current_frame == atlas->current_frame){ return; }
		LOG(DEBUG) << "dir" << (int)atlas->current_direction << std::endl;

		atlas->current_animation.texture->shift = atlas->current_animation.positions.find(atlas->current_direction)->second[current_frame];

		if(current_frame >= atlas->current_animation.frame_count-1){
			if(!atlas->loop){return;}
			atlas->start_time = current_time;
			atlas->current_frame = 0;
		}
	}

	void TextureAnimator::OnMessage(AnimationCommand message){
		Atlas* atlas = ecs::GetComponent<Atlas>(message.dest);
		if(!atlas){ return; }

		switch(message.action){
			case AnimationAction::PLAY:
				atlas->loop = message.loop;
				Play(atlas, message.name, message.direction);
				break;
			case AnimationAction::PAUSE:
				Pause(atlas);
				break;
			case AnimationAction::STOP:
				Stop(atlas);
				break;
		}
	}

	void TextureAnimator::Play(Atlas* atlas, std::string animation_name, Direction d){

		// don't play the animation if it is already playing
		if( atlas->play && (atlas->current_animation.name == animation_name) ){
			if(d == Direction::LAST){ return; }
			if(d == atlas->current_direction){ return; }
		}

		LOG(DEBUG) << "Playing " << animation_name << std::endl;
		auto it = atlas->animations.find(animation_name);
		if(it == atlas->animations.end()){ return; } // Animation not found

		// don't play the animation if it has a lower priority
		//if(it->second.priority >= this->current_priority
		//		&& this->current_priority != -1){ return; }

		if(d != Direction::LAST){
			atlas->current_direction = d;
		}
		atlas->current_animation = atlas->animations.find(animation_name)->second;
		//this->current_priority = it->second.priority;
		atlas->start_time = Time::GetCurrentTime();
		atlas->current_frame = -1;
		atlas->play = true;
	}

	void TextureAnimator::Pause(Atlas* atlas){
		atlas->play = false;
	}

	void TextureAnimator::Stop(Atlas* atlas){
		Pause(atlas);
		atlas->current_frame = 0;
	}
}
