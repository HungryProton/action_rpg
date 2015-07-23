#ifndef TEST_GAME_HPP
#define TEST_GAME_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "game.hpp"

namespace game{

    const lest::test game[] = {
        
        CASE("Should start the game"){
            Game::Start();
        },

    };

    static int run_game_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Game test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( game, argc, argv, std::cout );
    }
}

#endif //TEST_TOOLS_LOGGER_HPP
