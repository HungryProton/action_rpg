#define lest_FEATURE_COLOURISE 1

#include "deps/lest.hpp"

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

