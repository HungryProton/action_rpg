#ifndef GAME_ECS_ENTITY_HPP_
#define GAME_ECS_ENTITY_HPP_

namespace game{

	struct Entity{
		unsigned long uid;

		Entity(){ uid = 0; }
		Entity(unsigned long i){ uid = i; }
	};
}
#endif //GAME_ECS_ENTITY_HPP_
