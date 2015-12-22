#ifndef GAME_CORE_MESSAGING_RENDERING_INTENT_HPP
#define GAME_CORE_MESSAGING_RENDERING_INTENT_HPP

#include "../message.hpp"
#include "core/entity/component/drawable.hpp"

namespace game{

	enum Action{
		RI_NONE,
		RI_RENDER_DRAWABLE,
		RI_ACTIVE_CAMERA
	};

	struct RenderingIntent : public Message{
		Action action;
		Drawable* drawable;
		GameObject* camera;
	};
}
#endif //GAME_CORE_MESSAGING_RENDERING_INTENT_HPP
