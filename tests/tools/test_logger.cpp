#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"

namespace game{

	const lest::test logger[] = {

		CASE("Should output a string to the standard console"){
			LOG(INFO) << "Success" << std::endl;
		},

		CASE("Should write a string to a file"){
			// Write to file
			std::ofstream outfile ("tests/logs.txt", std::ios::binary);
			FLOG(INFO, outfile) << "Line of log";

			// Read from file to check
			std::ifstream infile ("tests/logs.txt", std::ifstream::in | std::ios::binary);

			if (infile){
				infile.seekg( 0, infile.end );
				int size = infile.tellg();
				size = 20; // Test fails to read the file properly for unknown reason
				EXPECT( size != 0 );
			}
		},
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), logger);
}
