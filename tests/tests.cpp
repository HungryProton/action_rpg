// Include all test suites 
#include "tools/test_logger.hpp"
//#include "test_game.hpp"
#include "core/service/test_render.hpp"
#include "core/locator/test_locator.hpp"
#include "core/entity/test_component.hpp"
#include "core/service/test_image_helper.hpp"

using namespace std;

int main( int argc, char * argv[] ){

    game::run_logger_test_suite(argc, argv);
    game::run_locator_test_suite(argc, argv);
    game::run_components_test_suite(argc, argv);
    game::run_image_helper_test_suite(argc, argv);
    game::run_render_test_suite(argc, argv);

    //game::run_game_test_suite(argc, argv);

    return EXIT_SUCCESS;
}

