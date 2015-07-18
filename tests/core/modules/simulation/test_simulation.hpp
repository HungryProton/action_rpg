#ifndef TEST_MODULE_SIMULATION_HPP
#define TEST_MODULE_SIMULATION_HPP

#include <iostream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/modules/simulation/simulation.hpp"

namespace game{

    const lest::test simulation[] = {{
        
        CASE("Should start and stop the simulation module without errors"){
            Simulation* simulation_module = new Simulation();
            simulation_module->Start();

            EXPECT( simulation_module->GetState() == RUNNING ); 

            simulation_module->Stop();

            EXPECT( simulation_module->GetState() == EXITING );
        },

    }};

    static int run_simulation_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Simulation test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( simulation, argc, argv, std::cout );
    }
}

#endif //TEST_MODULE_RENDER_HPP
