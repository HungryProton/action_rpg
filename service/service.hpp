#ifndef GAME_SERVICE_FACADE_HPP
#define GAME_SERVICE_FACADE_HPP

#include "locator/locator.hpp"

namespace game{

	class Service{
		public:
			template <class T>
			static T* Get();

			static void ClearMemory();
		private:
			template <class T>
			static T* Create();

			static Locator locator_;
	};
}

#include "service.tcc"
#endif //GAME_SERVICE_FACADE_HPP
