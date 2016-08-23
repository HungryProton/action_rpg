#include "player_controllable.hpp"

namespace game{

	PlayerControllable::PlayerControllable(){
		player_id = 0;
	}

	PlayerControllable::PlayerControllable(int id){
		player_id = id;
	}
}
