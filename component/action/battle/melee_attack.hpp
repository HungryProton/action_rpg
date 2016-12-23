#ifndef GAME_COMPONENT_ACTION_BATTLE_MELEE_ATTACK_HPP
#define GAME_COMPONENT_ACTION_BATTLE_MELEE_ATTACK_HPP

namespace game{

	struct MeleeAttack{
		int damage; 	// Probability to slain the ennemy in one hit
		float attack_duration;
		bool is_attacking;
		float start_time;

		MeleeAttack(int);
	};
}

#endif //GAME_COMPONENT_ACTION_BATTLE_MELEE_ATTACK_HPP
