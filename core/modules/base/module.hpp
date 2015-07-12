#ifndef CORE_MODULE_HPP
#define CORE_MODULE_HPP

#include <thread>
#include "tools/message.hpp"

namespace game{

    enum ModuleState{UNINITIALIZED, RUNNING, PAUSED, EXITING};

    class Module{
        public:
            Module();
            virtual ~Module();

            virtual void Start();
            virtual void Stop();
            virtual void HandleMessage(Message m) = 0;
            ModuleState GetState();

        protected:
            virtual void Run() = 0;

            bool initialized_;
            std::thread* thread_;

            ModuleState module_state_;
    };
}

#endif //CORE_MODULE_HPP
