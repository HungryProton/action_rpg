#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "core/messaging/message_bus.hpp"
#include "dummy_handler.hpp"

namespace game{

	//util
	unsigned long GetMessagesCount(){
		return MessageBus::GetHealthReport().received_messages_count;
	}

	const lest::test messaging_test[] = {

		SCENARIO("Communication should be possible within the game parts"){

			GIVEN("given an empty message bus and two valid messages handler"){
				MessageBus::ResetHealthReport();
				MessageBusHealthReport message_bus_report;

				DummyHandler* m1 = new DummyHandler();
				DummyHandler* m2 = new DummyHandler();

				THEN("handler should have registered itself to the message bus"){
					message_bus_report = MessageBus::GetHealthReport();
					EXPECT(message_bus_report.registered_handler_count == 2);
				}
				THEN("handler should be able to broadcast messages through the message bus"){
          m1->SendDummyMessage();
          m2->Process();

					EXPECT(GetMessagesCount() == 1);
				}
				THEN("handler should be able to receive messages"){
					m1->SendDummyMessage();
					m2->Process();

					EXPECT(m2->GetReceivedMessagesCount() == 1);
				}
				THEN("handler should deregister from the message bus upon destruction"){
          delete m1;
          delete m2;

					message_bus_report = MessageBus::GetHealthReport();
					EXPECT(message_bus_report.registered_handler_count == 0);
				}
			}
		}
	};

	// Register this test to be ran automatically
	extern lest::tests & specifications();
	lest_ADD_MODULE( specifications(), messaging_test )
}
