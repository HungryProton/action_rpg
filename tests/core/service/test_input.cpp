#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "core/service/input/input.hpp"
#include "core/messaging/input_message.hpp"

namespace game{

    class DummyMessageHandler : public IMessageHandler{
        public:
            void On(InputMessage){
                received = true;
            }

            bool received = false;
    };

    const lest::test input[] = {

        CASE( "Should send messages" ){
            Input inputService;
            DummyMessageHandler object;

            inputService.RegisterListener( &object );
        },
    };

    extern lest::tests& specification();
    MODULE( specification(), input);
}
