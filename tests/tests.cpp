#include "deps/lest.hpp"

using namespace std;

namespace game{

    lest::tests & specifications(){
        static lest::tests tests;
        return tests;
    }

    int RunRegisteredTests( int argc, char** argv ){
        return lest::run( specifications(), lest::texts(argv + 1, argv + argc) );
    }
}

int main( int argc, char** argv ){
    game::RunRegisteredTests( argc, argv );
    return EXIT_SUCCESS;
}

