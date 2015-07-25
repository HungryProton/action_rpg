#ifndef GAME_LOCATOR_HPP
#define GAME_LOCATOR_HPP

#include <map>
#include <typeindex>
#include "core/services/service.hpp"

namespace game{

    class Locator{
        public:
            static void Provide(Service*);
            static void Remove(Service*);

            template <class T>
            static T* Get();

        private:
            static std::map<std::type_index, Service*> services_;
    };
}

#include "locator.tcc"

#endif //GAME_LOCATOR_HPP
