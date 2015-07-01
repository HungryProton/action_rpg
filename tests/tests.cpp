// Include all test suites 
#include "tools/test_logger.hpp"

using namespace std;

int main( int argc, char * argv[] ){

    game::run_logger_test_suite(argc, argv);

    return EXIT_SUCCESS;
}

