#ifndef GAME_ECS_COMPONENT_HPP_
#define GAME_ECS_COMPONENT_HPP_

#include <unordered_map>
#include "entity.hpp"

namespace game{

	template<class T>
	class Component{
		public:
			static T* CreateForEntity(Entity);
			static T* GetFromEntity(Entity);
			static void DeleteFromEntity(Entity);

		private:
			static std::unordered_map<unsigned long, T*> components_;
	};
}

#include "component.tcc"
#endif //GAME_ECS_COMPONENT_HPP_
