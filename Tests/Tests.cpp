// Include all test suites 
#include "Core/Modules/Module.hpp"
#include "Core/Modules/Game.hpp"
#include "Core/Modules/Render.hpp"

using namespace std;

int main( int argc, char * argv[] ){

    /*
     * Modules test suites
     */
    game::run_module_test_suite(argc, argv);
    game::run_game_module_test_suite(argc, argv);
    game::run_render_module_test_suite(argc, argv);

    return EXIT_SUCCESS;
}

