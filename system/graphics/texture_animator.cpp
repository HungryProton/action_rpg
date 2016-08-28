#include "texture_animator.hpp"
#include "component/atlas.hpp"
#include "common/time.hpp"

namespace game{

	TextureAnimator::TextureAnimator() : System(){ }

	TextureAnimator::~TextureAnimator(){ }

	void TextureAnimator::OnUpdate(Entity e){
		Atlas* atlas = ecs::GetComponent<Atlas>(e);

		float current_time = Time::GetCurrentTime();
		float elapsed_time = current_time - atlas->start_time;
		int current_frame = (int)(elapsed_time*24.f);
		if(current_frame == atlas->current_frame){ return; }

		if(current_frame == atlas->frame_count){
			if(!tex->loop){return;}
			tex->start_time = current_time;
			tex->current_frame = current_frame;
		}
	}

	void TextureAnimator::OnMessage(AnimationCommand command){

	}

}
