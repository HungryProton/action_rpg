#ifndef GAME_CORE_CONCRETE_HELPER_HPP
#define GAME_CORE_CONCRETE_HELPER_HPP

namespace game{
    
    class ConcreteHelper{
        public:
            virtual ~ConcreteHelper(){};
            virtual void ClearMemory() = 0;
    };
}

#endif // GAME_CORE_CONCRETE_HELPER_HPP

