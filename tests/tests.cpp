// Include all test suites 
#include "core/test_game.hpp"
#include "core/modules/test_render.hpp"
#include "tools/test_logger.hpp"

using namespace std;

int main( int argc, char * argv[] ){

    game::run_logger_test_suite(argc, argv);
    game::run_render_test_suite(argc, argv);

    return EXIT_SUCCESS;
}

