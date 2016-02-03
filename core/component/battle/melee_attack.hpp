#ifndef GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP
#define GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP

#include "../component.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

namespace game{

	struct MeleeAttack : public Component,
											 public MessageHandler<InputMessage>{
		std::string animation_name;
		float damage_modifier;


		MeleeAttack();
		MeleeAttack(GameObject*);
		MeleeAttack(MeleeAttack*);
		virtual MeleeAttack* Clone();
		virtual void Update();

		private:
			void ProcessReceivedMessages();
			void Attack();
	};
}

#endif //GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP
