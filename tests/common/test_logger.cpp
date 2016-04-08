#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/logger.hpp"

namespace game{

	const lest::test logger[] = {

		CASE("Should write a string to a file"){
			// Write to file
			std::ofstream outfile ("tests/data/logs.txt", std::ios::binary);
			FLOG(INFO, outfile) << "Line of log" << std::endl;
			outfile.close();

			// Read from file to check
			std::ifstream infile ("tests/data/logs.txt", std::ifstream::in | std::ios::binary);

			if (infile){
				infile.seekg( 0, infile.end );
				int size = infile.tellg();
				LOG(DEBUG) << size << std::endl;
				EXPECT( size != 0 );
				infile.close();
			} else {
				std::string err = "Could not open file tests/data/logs.txt";
				EXPECT(err == "");
			}
		},
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), logger);
}
