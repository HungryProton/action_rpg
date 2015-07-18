#ifndef CORE_MODULE_SIMULATION_HPP
#define CORE_MODULE_SIMULATION_HPP

#include "core/modules/base/module.hpp"
#include "core/messaging/message.hpp"

namespace game{

    class Simulation : public Module{

        public:
            Simulation();
            ~Simulation();

            void HandleMessage(Message msg);

        private:
            void Run();

    };
}
#endif //CORE_MODULE_SIMULATION_HPP
