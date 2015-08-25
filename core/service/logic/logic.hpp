#ifndef CORE_SERVICE_LOGIC_HPP
#define CORE_SERVICE_LOGIC_HPP

#include "core/service/service.hpp"

namespace game{

    class Logic : public CoreService{

        public:
            Logic();
            ~Logic();

            void Initialize();

            void ClearMemory();
            void Update();

        private:




    };
}

#include "logic.tcc"

#endif
