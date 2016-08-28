#ifndef GAME_SYSTEM_GRAPHICS_TEXTURE_ANIMATOR_HPP_
#define GAME_SYSTEM_GRAPHICS_TEXTURE_ANIMATOR_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/animation_command.hpp"
#include "component/atlas.hpp"

namespace game{

	class TextureAnimator : public System,
													public MessageHandler<AnimationCommand>{
		public:
			TextureAnimator();
			~TextureAnimator();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(AnimationCommand);

			void Play(Atlas*, std::string, Direction);
			void Pause(Atlas*);
			void Stop(Atlas*);
	};
}

#endif //GAME_SYSTEM_GRAPHICS_TEXTURE_ANIMATOR_HPP_
