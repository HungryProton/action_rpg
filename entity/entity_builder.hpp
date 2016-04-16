#ifndef GAME_ENTITY_ENTITY_BUILDER_HPP
#define GAME_ENTITY_ENTITY_BUILDER_HPP

#include <queue>

namespace game{

	class EntityBuilder{
		public:
			EntityBuilder();
			~EntityBuilder();
			unsigned long Create();
			void NotifyDelete(unsigned long);

		private:
			unsigned long last_generated_id_;
			std::queue<unsigned long> unused_id_list_;
	};
}

#endif //GAME_ENTITY_ENTITY_BUILDER_HPP
