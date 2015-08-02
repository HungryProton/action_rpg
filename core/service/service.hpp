#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

namespace game{

    class Service{
        public:
            virtual ~Service(){};
            virtual void ClearMemory() = 0;
    };

    class CoreService : public Service{
        public:
            virtual ~CoreService(){};
            virtual void ClearMemory() = 0;
            virtual void Update() = 0;
    };
}

#endif //GAME_SERVICE_HPP

