#ifndef GAME_CORE_MESSAGING_MESSAGE_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HPP

namespace game{

	struct Message{
		int message_id;
		bool children_recursive;
	};
}

#endif //GAME_CORE_MESSAGING_MESSAGE_HPP
