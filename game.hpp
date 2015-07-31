#ifndef GAME_HPP
#define GAME_HPP

#include "core/service/render/render.hpp"

namespace game{

    enum State{ UNINITIALIZED, RUNNING, EXITING };

    class Game{
        public:
            static void Initialize();
            static void Play();
            static void Stop();

            static State GetState();

        private:
            static void ClearMemory();
            static Render* render_;
            static State state_;
    };
}

#endif //GAME_HPP
