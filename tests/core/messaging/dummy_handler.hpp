#ifndef GAME_TEST_DUMMY_HANDLER_HPP
#define GAME_TEST_DUMMY_HANDLER_HPP

#include "core/messaging/message.hpp"
#include "core/messaging/message_handler.hpp"

namespace game{

  class DummyHandler : public MessageHandler<Message>{
    public:
      DummyHandler();
			~DummyHandler();
      void Process();
      void SendDummyMessage();
      int GetReceivedMessagesCount();

    private:
      int received_messages_count_;
  };
}

#endif //GAME_TEST_DUMMY_HANDLER_HPP
