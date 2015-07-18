// Include all test suites 
#include "core/test_game.hpp"
#include "core/modules/render/test_render.hpp"
#include "core/modules/simulation/test_simulation.hpp"
#include "tools/test_logger.hpp"

using namespace std;

int main( int argc, char * argv[] ){

    game::run_logger_test_suite(argc, argv);
    game::run_render_test_suite(argc, argv);
    game::run_simulation_test_suite(argc, argv);

    return EXIT_SUCCESS;
}

