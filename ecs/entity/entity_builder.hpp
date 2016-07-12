#ifndef GAME_ENTITY_ENTITY_BUILDER_HPP
#define GAME_ENTITY_ENTITY_BUILDER_HPP

#include <vector>
#include "entity.hpp"

namespace game{

	class EntityBuilder{
		public:
			EntityBuilder();
			~EntityBuilder();
			Entity Create();
			void NotifyDeletionOf(Entity);

		private:
			unsigned long last_generated_id_;
			std::vector<unsigned long> unused_id_list_;
	};
}

#endif //GAME_ENTITY_ENTITY_BUILDER_HPP
