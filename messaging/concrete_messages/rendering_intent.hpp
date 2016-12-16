#ifndef GAME_CORE_MESSAGING_RENDERING_INTENT_HPP
#define GAME_CORE_MESSAGING_RENDERING_INTENT_HPP

#include "../message.hpp"
#include "component/graphic/drawable.hpp"

namespace game{

	enum class RIntent{
		NONE,
		SET_ACTIVE_CAMERA
	};

	struct RenderingIntent : public Message{
		RIntent action;
	};
}
#endif //GAME_CORE_MESSAGING_RENDERING_INTENT_HPP
