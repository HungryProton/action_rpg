#include "common/logger.hpp"
#include "common/random.hpp"
#include "dummy_handler.hpp"
#include "messaging/message.hpp"
#include "message_bus_stub.hpp"

namespace game{

  DummyHandler::DummyHandler() : MessageHandler<Message>(){
		MessageBusStub::RegisterHandler(this);
    this->received_messages_count_ = 0;
  }

	DummyHandler::~DummyHandler(){
		MessageBusStub::DeregisterHandler(this);
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
		MessageBusStub::Push(message);
  }

  int DummyHandler::GetReceivedMessagesCount(){
    return this->received_messages_count_;
  }
}
