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
		std::vector<int> attacks_durations; // In frames
		int current_attack;

		MeleeAttack();
		MeleeAttack(GameObject*);
		MeleeAttack(MeleeAttack*);
		virtual MeleeAttack* Clone();
		virtual void Update();

		private:
			float start_time;
			void Attack();
			virtual void OnMessage(InputMessage);
			void SendDamageMessage();
	};
}

#endif //GAME_CORE_COMPONENT_BATTLE_MELEE_ATTACK_HPP
