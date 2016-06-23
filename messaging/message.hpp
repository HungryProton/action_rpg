#ifndef GAME_CORE_MESSAGING_MESSAGE_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HPP

namespace game{

	struct Message{
		Entity id;
		Entity from_id;
		Entity dest_id;
	};
}

#endif //GAME_CORE_MESSAGING_MESSAGE_HPP
