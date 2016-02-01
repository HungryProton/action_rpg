#ifndef CORE_MESSAGING_CONCRETE_MESSAGE_PHYSIC_INTENT_HPP
#define CORE_MESSAGING_CONCRETE_MESSAGE_PHYSIC_INTENT_HPP

#include "core/entity/game_object.hpp"
#include "../message.hpp"
#include <glm/glm.hpp>

namespace game{

	enum class PhysicAction{ADD_COLLIDER, APPLY_FORCE};

	struct PhysicIntent : public Message{
		GameObject* game_object;
		PhysicAction action;
		glm::vec3 force;
	};
}
#endif //CORE_MESSAGING_CONCRETE_MESSAGE_PHYSIC_INTENT_HPP
