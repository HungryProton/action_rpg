#include "dummy_handler.hpp"
#include "core/messaging/message.hpp"
#include "core/messaging/message_bus.hpp"

namespace game{

  DummyHandler::DummyHandler() : MessageHandler<Message>(){
    this->received_messages_count_ = 0;
  }

  void DummyHandler::Process(){
		for(Message message : this->MessageHandler<Message>::messages){
			this->received_messages_count_++;
		}
  }

  void DummyHandler::SendDummyMessage(){
    Message* message = new Message();
		MessageBus::Push(message);
		delete message;
  }

  int DummyHandler::GetReceivedMessagesCount(){
    return this->received_messages_count_;
  }
}
