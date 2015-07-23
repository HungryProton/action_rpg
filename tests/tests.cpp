// Include all test suites 
#include "tools/test_logger.hpp"
#include "test_game.hpp"

using namespace std;

int main( int argc, char * argv[] ){

    game::run_logger_test_suite(argc, argv);
    game::run_game_test_suite(argc, argv);

    return EXIT_SUCCESS;
}

