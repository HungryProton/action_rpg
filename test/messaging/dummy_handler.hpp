#ifndef GAME_TEST_DUMMY_HANDLER_HPP
#define GAME_TEST_DUMMY_HANDLER_HPP

#include "messaging/message.hpp"
#include "messaging/message_handler.hpp"

namespace game{

  class DummyHandler : public MessageHandler<Message>{
    public:
      DummyHandler();
			~DummyHandler();
      void Process();
      void SendDummyMessage();
      int GetReceivedMessagesCount();

    private:
			virtual void OnMessage(Message);
      int received_messages_count_;
  };
}

#endif //GAME_TEST_DUMMY_HANDLER_HPP
