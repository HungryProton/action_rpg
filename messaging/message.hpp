#ifndef GAME_CORE_MESSAGING_MESSAGE_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HPP

namespace game{

	struct Message{
		unsigned long id;
		unsigned long from_id;
		unsigned long dest_id;
	};
}

#endif //GAME_CORE_MESSAGING_MESSAGE_HPP
