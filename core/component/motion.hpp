#ifndef GAME_CORE_ENTITY_SYSTEM_MOTION_HPP
#define GAME_CORE_ENTITY_SYSTEM_MOTION_HPP

#include "component.hpp"
#include "transform.hpp"
#include <glm/glm.hpp>

namespace game{

	enum MotionType{SIMPLE, SERVO_CONTROL};

	struct Motion : public Component{
		public:
			MotionType type;
			glm::vec3 direction;
			glm::vec3 rotation;
			glm::vec3 scale;
			glm::vec3 max_force;
			float target_speed;

			// Helpers
			Motion();
			Motion(GameObject*);
			Motion(Motion*);
			~Motion();

			virtual void NotifyNewComponentAdded();
			virtual void Update();
			virtual Motion* Clone();

		private:
			// Target component
			Transform* transform;

			void SimpleResolve();
			void ServoResolve();
	};
}

#endif //GAME_CORE_ENTITY_SYSTEM_MOTION_HPP
