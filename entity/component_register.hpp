#ifndef GAME_ENTITY_COMPONENT_REGISTER_HPP
#define GAME_ENTITY_COMPONENT_REGISTER_HPP

#include <map>

namespace game{

	template<class T>
	class ComponentRegister{
		public:
			static void AddComponent(unsigned long, T*);
			static T* GetComponent(unsigned long);

		private:
			static std::map<unsigned long, T*> components_;
	};
}

#include "component_register.tcc"
#endif //GAME_ENTITY_COMPONENT_REGISTER_HPP
