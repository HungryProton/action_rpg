#ifndef GAME_ENTITY_SYSTEM_REGISTER_HPP
#define GAME_ENTITY_SYSTEM_REGISTER_HPP

#include <map>
#include <typeindex>
#include "system/system.hpp"
#include "core/game.hpp"

namespace game{

	class SystemRegister{
		friend Game;
		public:
			template<class T>
			static T* CreateSystem(float t = -1);

			template<class T>
			static T* Get();

		protected:
			static void Initialize();
			static void Update();
			static void ClearMemory();


			static std::map<std::type_index, System*> systems_;
	};
}

#include "system_register.tcc"
#endif //GAME_ENTITY_SYSTEM_REGISTER_HPP
