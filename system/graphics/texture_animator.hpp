#ifndef GAME_SYSTEM_GRAPHICS_TEXTURE_ANIMATOR_HPP_
#define GAME_SYSTEM_GRAPHICS_TEXTURE_ANIMATOR_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/animation_command.hpp"

namespace game{

	class TextureAnimator : public System,
													public MessageHandler<AnimationCommand>{
		public:
			TextureAnimator();
			~TextureAnimator();

		protected:
			void OnUpdate(Entity);
			void OnMessage(AnimationCommand);
	};
}

#endif //GAME_SYSTEM_GRAPHICS_TEXTURE_ANIMATOR_HPP_
