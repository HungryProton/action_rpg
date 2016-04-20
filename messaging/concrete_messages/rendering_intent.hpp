#ifndef GAME_CORE_MESSAGING_RENDERING_INTENT_HPP
#define GAME_CORE_MESSAGING_RENDERING_INTENT_HPP

#include "../message.hpp"
#include "component/drawable.hpp"

namespace game{

	enum Action{
		RI_NONE,
		RI_RENDER_DRAWABLE,
		RI_ACTIVE_CAMERA
	};

	struct RenderingIntent : public Message{
		Action action;
	};
}
#endif //GAME_CORE_MESSAGING_RENDERING_INTENT_HPP
