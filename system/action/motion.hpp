#ifndef GAME_SYSTEM_MOTION_HPP_
#define GAME_SYSTEM_MOTION_HPP_

#include "system/system.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "component/transform.hpp"
#include "component/motion.hpp"

namespace game{

	class MotionSystem : public System{
		public:
			MotionSystem();
			~MotionSystem();

		protected:
			void OnUpdate(Entity);
			void SimpleResolve(Motion*, Transform*);
			void ServoResolve(Motion*, Transform*);
	};
}

#endif //GAME_SYSTEM_MOTION_HPP_
