#ifndef GAME_CORE_HELPER_HPP
#define GAME_CORE_HELPER_HPP

#include <map>
#include <typeindex>

namespace game{

    class Helper{
        public:
            template<class T>
            static T* Get();

        private:
            static std::multimap<std::type_index, ConcreteHelper*> helpers_;
    };
}

#include "helper.tcc"

#endif //GAME_CORE_HELPER_HPP
