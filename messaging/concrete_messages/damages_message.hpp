#ifndef GAME_CORE_MESSAGING_CONCRETE_MESSAGE_HPP
#define GAME_CORE_MESSAGING_CONCRETE_MESSAGE_HPP

#include "../message.hpp"
#include "core/entity/game_object.hpp"
#include "core/component/common.hpp"

namespace game{

	enum class DamagesType{SLASH, CRUSH, BURN, SHOCK};

	struct DamagesMessage : public Message{
		float amount;
		DamagesType type;
		GameObject* origin;
		Area area_of_effect;
	};
}

#endif //GAME_CORE_MESSAGING_CONCRETE_MESSAGE_HPP
