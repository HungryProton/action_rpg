#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "core/service/service.hpp"

namespace game{

    enum State{ UNINITIALIZED, RUNNING, EXITING };

    class Game{
        public:
            static void Initialize();
            static void Play();
            static void Stop();

            static State GetState();

            // Any class can call this to ask to instantiate the given service, 
            // it will then be available anywhere from the service locator
            template<class T>
            static void RequestForService();

            template<class T>
            static void RequestForCoreService();

        private:
            static void ClearMemory();

            template<class T>
            static void DeleteServices(std::vector<T*>*);

            static std::vector<CoreService*> core_services_;
            static std::vector<Service*> secondary_services_;
            static State state_;
    };
}

#include "game.tcc"

#endif //GAME_HPP
