#include "deps/lest.hpp"

using namespace std;

namespace game{

    lest::tests& specification(){
        static lest::tests tests;
        return tests;
    }
    
    int RunTests( int argc, char** argv ){
        return lest::run(specification(), argc, argv);
    }
}

int main( int argc, char** argv ){
    game::RunTests( argc, argv );
    return EXIT_SUCCESS;
}

