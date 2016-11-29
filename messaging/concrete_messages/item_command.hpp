#ifndef GAME_MESSAGING_CONCRETE_MESSAGE_ITEM_COMMAND_HPP_
#define GAME_MESSAGING_CONCRETE_MESSAGE_ITEM_COMMAND_HPP_

#include "messaging/message.hpp"

namespace game{

	enum class ItemAction{USE, PICKUP, DROP};

	struct ItemCommand : public Message{
		ItemAction action;
	};
}

#endif //GAME_MESSAGING_CONCRETE_MESSAGE_ITEM_COMMAND_HPP_
