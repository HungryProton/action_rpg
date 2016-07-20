#ifndef GAME_LOCATOR_HPP
#define GAME_LOCATOR_HPP

#include <map>
#include <typeindex>

namespace game{

	class ServiceWorker;
	class Locator{
		public:
			template <class T>
			T* Get();

			// Also transfer ownership
			void Transfer(ServiceWorker*);
			void ClearMemory();
		private:
			std::map<std::type_index, ServiceWorker*> services_;
	};
}

#include "locator.tcc"

#endif //GAME_LOCATOR_HPP
