#ifndef GAME_ENTITY_ENTITY_BUILDER_HPP
#define GAME_ENTITY_ENTITY_BUILDER_HPP

#include <vector>

namespace game{

	class EntityBuilder{
		public:
			EntityBuilder();
			~EntityBuilder();
			Entity Create();
			void NotifyDelete(Entity);

		private:
			Entity last_generated_id_;
			std::vector<Entity> unused_id_list_;
	};
}

#endif //GAME_ENTITY_ENTITY_BUILDER_HPP
