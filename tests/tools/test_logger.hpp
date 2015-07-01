#ifndef TEST_TOOLS_LOGGER_HPP
#define TEST_TOOLS_LOGGER_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"

namespace game{

    const lest::test logger[] = {
        
        CASE("Should output a string to the standard console"){
            log(INFO) << "Success" << std::endl;
        },

        CASE("Should write a string to a file"){
            // Write to file
            std::ofstream outfile ("tests/logs.txt", std::ios::binary | std::ios::ate);
            flog(INFO, outfile) << "Line of log";

            // Read from file to check 
            std::ifstream infile ("tests/logs.txt", std::ifstream::binary);

            if (infile){
                infile.seekg( 0, infile.end );
                int size = infile.tellg();
                EXPECT( size != 0 );
            }
        },
    };

    static int run_logger_test_suite(int argc, char** argv){

        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Logger test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( logger, argc, argv, std::cout );
    }
}

#endif //TEST_TOOLS_LOGGER_HPP
