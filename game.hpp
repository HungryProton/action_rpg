#ifndef GAME_HPP
#define GAME_HPP

#include "core/services/render/render.hpp"

namespace game{
    class Game{
        public:
            static void Start();

        private:
            static void Update();
            static Render* render_;
    };
}

#endif //GAME_HPP
