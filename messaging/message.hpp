#ifndef GAME_CORE_MESSAGING_MESSAGE_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HPP

#include "ecs/entity/entity.hpp"

namespace game{

	struct Message{
		unsigned long id;
		Entity from;
		Entity dest;
	};
}

#endif //GAME_CORE_MESSAGING_MESSAGE_HPP
