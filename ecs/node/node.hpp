#ifndef GAME_ECS_NODE_HPP_
#define GAME_ECS_NODE_HPP_

#include <vector>
#include "../entity/entity.hpp"

namespace game{

	template<class ...>
	class Node{
		public:
			static std::vector<Entity> GetEntityList();
			static void UpdateListWith(Entity);
			static void DeleteEntityFromList(Entity);

		private:
			static std::vector<Entity> entities_;
	};
}

#include "node.tcc"
#endif //GAME_ECS_CONCRETE_NODE_HPP_
