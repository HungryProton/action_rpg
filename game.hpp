#ifndef GAME_HPP
#define GAME_HPP

#include "core/services/render/render.hpp"

namespace game{

    enum State{ UNINITIALIZED, RUNNING, EXITING };

    class Game{
        public:
            static void Start();
            static void Stop();

            static State GetState();

        private:
            static void ClearMemory();
            static void Update();
            static Render* render_;
            static State state_;
    };
}

#endif //GAME_HPP
