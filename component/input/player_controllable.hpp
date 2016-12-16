#ifndef GAME_COMPONENT_PLAYER_CONTROLLABLE_HPP_
#define GAME_COMPONENT_PLAYER_CONTROLLABLE_HPP_

namespace game{

	struct PlayerControllable{
		int player_id;	// Allow for local multiplayer on same computer

		PlayerControllable();
		PlayerControllable(int);
	};
}

#endif //GAME_COMPONENT_PLAYER_CONTROLLABLE_HPP_
