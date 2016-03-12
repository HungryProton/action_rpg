#ifndef GAME_CORE_COMPONENT_DEATH_CONTROLLER_HPP
#define GAME_CORE_COMPONENT_DEATH_CONTROLLER_HPP

#include "behavior.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/messaging/concrete_messages/event_message.hpp"

namespace game{

	struct DeathController : public Behavior,
													 public MessageHandler<EventMessage>{

		bool delete_after_death;
		float delay_before_delete;
		std::string death_animation;

		DeathController();
		DeathController(GameObject*);
		DeathController(DeathController*);
		DeathController* Clone();
		void Update();

		private:
			void OnMessage(EventMessage);
	};
}
#endif //GAME_CORE_COMPONENT_DEATH_CONTROLLER_HPP
