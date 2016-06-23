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
			static T* Get();

			template<class T>
			static void AssociateEntityTo(unsigned long);

			template<class T>
			static void DissociateEntityFrom(unsigned long);

			static void DissociateEntityFromAll(unsigned long);
			static void CloneAssociationOfInto(unsigned long, unsigned long);

		private:
			static void Initialize();
			static void Update();
			static void ClearMemory();

			template<class T>
			static T* CreateSystem();

			static std::map<std::type_index, System*> systems_;
	};
}

#include "system_register.tcc"
#endif //GAME_ENTITY_SYSTEM_REGISTER_HPP
