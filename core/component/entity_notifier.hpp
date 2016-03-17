#ifndef CORE_CORE_COMPONENT_ENTITY_NOTIFIER_HPP
#define CORE_CORE_COMPONENT_ENTITY_NOTIFIER_HPP

#include "core/component/component.hpp"
#include "core/messaging/concrete_messages/event_message.hpp"
#include "core/messaging/message_handler.hpp"

namespace game{

	struct EntityNotifier : public Component,
													public MessageHandler<EventMessage>{
		float timer;
		float refresh_rate; //in seconds
		bool notify_position;
		bool notify_speed;

		EntityNotifier();
		EntityNotifier(GameObject*);
		EntityNotifier(EntityNotifier*);
		virtual EntityNotifier* Clone();
		virtual void Update();

		private:
			void OnMessage(EventMessage);
	};
}
#endif //CORE_CORE_COMPONENT_ENTITY_NOTIFIER_HPP
