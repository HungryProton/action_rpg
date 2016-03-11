#include "tools/logger.hpp"
#include "tools/random.hpp"
#include "dummy_handler.hpp"
#include "core/messaging/message.hpp"
#include "message_bus_testing.hpp"

namespace game{

  DummyHandler::DummyHandler() : MessageHandler<Message>(){
		MessageBusTesting::RegisterHandler(this);
    this->received_messages_count_ = 0;
  }

	DummyHandler::~DummyHandler(){
		MessageBusTesting::DeregisterHandler(this);
	}

  void DummyHandler::Process(){
		this->MessageHandler<Message>::UpdateMessages();
  }

	void DummyHandler::OnMessage(Message msg){
			this->received_messages_count_++;
	}


  void DummyHandler::SendDummyMessage(){
    Message message;
		message.id = Random::NextInt();
		MessageBusTesting::Push(message);
  }

  int DummyHandler::GetReceivedMessagesCount(){
    return this->received_messages_count_;
  }
}
