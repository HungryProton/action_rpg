#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "message_bus_stub.hpp"
#include "dummy_handler.hpp"

namespace game{

	const lest::test messaging_test[] = {

		SCENARIO("Communication should be possible within different entities"){

			GIVEN("given an empty message bus and two valid messages handler"){
				MessageBusStub::Reset();

				DummyHandler* m1 = new DummyHandler();
				DummyHandler* m2 = new DummyHandler();

				THEN("handler should have registered itself to the message bus"){
					EXPECT(MessageBusStub::GetRegisteredHandlerCount() == 2);
				}
				WHEN("a message is broadcasted to the message bus"){
					m1->SendDummyMessage();
					m2->Process();

					THEN("the message bus should have received a message"){
						EXPECT(MessageBusStub::GetReceivedMessagesCount() >= 1);
					}
					THEN("the message should have been dispatched to the handler"){
						EXPECT(m2->GetReceivedMessagesCount() >= 1);
					}
				}
				WHEN("a handler is registered, then deleted"){
					int count = MessageBusStub::GetRegisteredHandlerCount();
					DummyHandler* m3 = new DummyHandler();
					delete m3;

					THEN("it should have deregistered itself from the message bus"){
						EXPECT(MessageBusStub::GetRegisteredHandlerCount() == count);
					}
				}
				delete m1;
				delete m2;
			}
		}
	};

	// Register this test to be ran automatically
	extern lest::tests & specifications();
	lest_ADD_MODULE( specifications(), messaging_test )
}
