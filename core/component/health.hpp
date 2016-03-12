#ifndef GAME_CORE_COMPONENT_HEALTH_HPP
#define GAME_CORE_COMPONENT_HEALTH_HPP

#include "component.hpp"
#include "core/messaging/concrete_messages/damages_message.hpp"

namespace game{

	struct Health : public Component,
									public MessageHandler<DamagesMessage>{

		float amount;

		Health();
		Health(GameObject*);
		Health(Health*);
		virtual Health* Clone();
		virtual void Update();
		virtual void OnMessage(DamagesMessage);

		private:
			void TakeDamages(DamagesMessage);

	};
}

#endif //GAME_CORE_COMPONENT_HEALTH_HPP
