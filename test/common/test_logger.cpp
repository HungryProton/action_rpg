#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/logger.hpp"

namespace game{

	const lest::test logger[] = {

		CASE("Should write a string to a file"){
			std::string file_path = "test/data/logs.txt";
			// Write to file
			std::ofstream outfile (file_path, std::ios::binary);
			FLOG(INFO, outfile) << "Line of log" << std::endl;
			outfile.close();

			// Read from file to check
			std::ifstream infile (file_path, std::ifstream::in | std::ios::binary);

			if (infile){
				infile.seekg( 0, infile.end );
				int size = infile.tellg();
				EXPECT( size != 0 );
				infile.close();
			} else {
				std::string err = "Could not open file " + file_path;
				EXPECT(err == "");
			}
		},
		CASE("It should offer multiple LOG level"){
			LOG(INFO) << "Info" << std::endl;
			LOG(WARNING) << "Warning" << std::endl;
			LOG(DEBUG) << "Debug" << std::endl;
			LOG(ERROR) << "Error" << std::endl;
			LOG(CRITICAL) << "Critical" << std::endl;
			LOG(SILENT) << "Silent" << std::endl;
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), logger);
}
