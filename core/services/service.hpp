#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

namespace game{

    class Service{
        public:
            Service();
            virtual ~Service();
            virtual void ClearMemory() = 0;
    };
}

#endif //GAME_SERVICE_HPP

