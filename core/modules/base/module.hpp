#ifndef CORE_MODULE_HPP
#define CORE_MODULE_HPP

#include <thread>
#include "tools/message.hpp"

namespace game{

    class Module{
        public:
            Module();
            virtual ~Module();

            virtual void Start();
            virtual void Stop();
            virtual void HandleMessage(Message m) = 0;

        protected:
            virtual void Run() = 0;

            bool initialized_;
            std::thread* thread_;

    };
}

#endif //CORE_MODULE_HPP
