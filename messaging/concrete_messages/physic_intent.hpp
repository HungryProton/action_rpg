#ifndef CORE_MESSAGING_CONCRETE_MESSAGE_PHYSIC_INTENT_HPP
#define CORE_MESSAGING_CONCRETE_MESSAGE_PHYSIC_INTENT_HPP

#include "../message.hpp"
#include <glm/glm.hpp>

namespace game{

	enum class PhysicAction{APPLY_FORCE};

	struct PhysicIntent : public Message{
		PhysicAction action;
		glm::vec3 force;
	};
}
#endif //CORE_MESSAGING_CONCRETE_MESSAGE_PHYSIC_INTENT_HPP
