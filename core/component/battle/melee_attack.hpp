#ifndef GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP
#define GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP

#include "../behavior.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

namespace game{

	struct MeleeAttack : public Behavior,
											 public MessageHandler<InputMessage>{
		std::string animation_name;
		float damage_modifier;


		MeleeAttack();
		MeleeAttack(GameObject*);
		MeleeAttack(MeleeAttack*);
		virtual MeleeAttack* Clone();
		virtual void Update();

		float attack_duration;

		private:
			float start_time;
			void ProcessReceivedMessages();
			void Attack();
	};
}

#endif //GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP
