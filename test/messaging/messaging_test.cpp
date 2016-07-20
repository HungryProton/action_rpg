#include "deps/catch.hpp"
#include "message_bus_stub.hpp"
#include "dummy_handler.hpp"

namespace game{

	SCENARIO("Communication should be possible within different entities"){

		GIVEN("given an empty message bus and two valid messages handler"){
			MessageBusStub::Reset();

			DummyHandler* m1 = new DummyHandler();
			DummyHandler* m2 = new DummyHandler();

			THEN("handler should have registered itself to the message bus"){
				REQUIRE(MessageBusStub::GetRegisteredHandlerCount() == 2);
			}
			WHEN("a message is broadcasted to the message bus"){
				m1->SendDummyMessage();
				m2->Process();

				THEN("the message bus should have received a message"){
					REQUIRE(MessageBusStub::GetReceivedMessagesCount() >= 1);
				}
				THEN("the message should have been dispatched to the handler"){
					REQUIRE(m2->GetReceivedMessagesCount() >= 1);
				}
			}
			WHEN("a handler is registered, then deleted"){
				int count = MessageBusStub::GetRegisteredHandlerCount();
				DummyHandler* m3 = new DummyHandler();
				delete m3;

				THEN("it should have deregistered itself from the message bus"){
					REQUIRE(MessageBusStub::GetRegisteredHandlerCount() == count);
				}
			}
			delete m1;
			delete m2;
		}
	}
}
