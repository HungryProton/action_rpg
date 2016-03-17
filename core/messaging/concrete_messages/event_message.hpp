#ifndef GAME_CORE_MESSAGING_CONCRETE_MESSAGE_EVENT_HPP
#define GAME_CORE_MESSAGING_CONCRETE_MESSAGE_EVENT_HPP

#include "../message.hpp"
#include "core/entity/game_object.hpp"

namespace game{

	enum class EventType{DIED, ENTITY_EXISTS};

	struct EventMessage : public Message{
		EventType type;
		float date;	// When did the event happened?
		GameObject* object;	// Which gameObject is concerned?
	};
}
#endif //GAME_CORE_MESSAGING_CONCRETE_MESSAGE_EVENT_HPP
