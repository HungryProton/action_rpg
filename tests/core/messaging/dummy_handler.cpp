#include "tools/logger.hpp"
#include "tools/random.hpp"
#include "dummy_handler.hpp"
#include "core/messaging/message.hpp"
#include "core/messaging/message_bus.hpp"

namespace game{

  DummyHandler::DummyHandler() : MessageHandler<Message>(){
    this->received_messages_count_ = 0;
  }

  void DummyHandler::Process(){
		for(Message message : this->MessageHandler<Message>::messages_){
			LOG(INFO) << "msg id : " << message.id << std::endl;
			this->received_messages_count_++;
		}
  }

  void DummyHandler::SendDummyMessage(){
    Message message;
		message.id = Random::NextInt();
		MessageBus::Push(message);
  }

  int DummyHandler::GetReceivedMessagesCount(){
    return this->received_messages_count_;
  }
}
