#include "message_bus.hpp"

namespace game{

	void MessageBus::ResetHealthReport(){
		health_report_.received_messages_count = 0;
		health_report_.registered_handler_count = 0;
	}

	MessageBusHealthReport MessageBus::GetHealthReport(){
		return health_report_;
	}

	MessageBusHealthReport MessageBus::health_report_;
}
