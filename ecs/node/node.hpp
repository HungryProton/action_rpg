#ifndef GAME_ECS_NODE_HPP_
#define GAME_ECS_NODE_HPP_

#include <vector>
#include "../entity/entity.hpp"

namespace game{

	class BaseNode{
		public:
			BaseNode(){};
			virtual void UpdateListWith(Entity) = 0;
			virtual void DeleteEntityFromList(Entity) = 0;
	};

	template<class ...>
	class Node : public BaseNode{
		public:
			Node();
			~Node();

			std::vector<Entity> GetEntityList();
			void UpdateListWith(Entity);
			void DeleteEntityFromList(Entity);

		private:
			std::vector<Entity> entities_;
	};
}

#include "node.tcc"
#endif //GAME_ECS_CONCRETE_NODE_HPP_
