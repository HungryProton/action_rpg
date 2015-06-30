#ifndef TEST_TOOLS_LOGGER_HPP
#define TEST_TOOLS_LOGGER_HPP

#include "tools/logger.hpp"

namespace game{

    const lest::test logger[] = {

        CASE("Should create a valid logger"){
            Logger* = Logger(INFO);
           // REQUIRE( logger not null ) 
        },
        
        CASE("Should output a string to the standard console"){

        },

        CASE("Should write a string to a file"){

        },
    }

    static int run_logger_test(int argc, char** argv){
        lest::run( logger, argc, argv, std::cout );
    }
}

#endif //TEST_TOOLS_LOGGER_HPP
