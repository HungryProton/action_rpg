#ifndef GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP
#define GAME_CORE_MESSAGING_MESSAGE_HANDLER_HPP

//#include "message.hpp"
//#include "input_message.hpp"

namespace game{

    struct Message;
    struct InputMessage;

    class IMessageHandler{
        public:
            virtual void On(Message);
            virtual void On(InputMessage);
    };
}
#endif //GAME_MESSAGING_MESSAGE_HANDLER_HPP

