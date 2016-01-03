#ifndef GAME_CORE_ENTITY_SYSTEM_MOTION_HPP
#define GAME_CORE_ENTITY_SYSTEM_MOTION_HPP

#include "component.hpp"
#include "transform.hpp"
#include <glm/glm.hpp>

namespace game{

	enum MotionType{SIMPLE, SERVO_CONTROL};

	struct Motion : public Component{
		public:
			MotionType type_;
			glm::vec3 direction_;
			glm::vec3 rotation_;
			glm::vec3 scale_;
			glm::vec3 max_force_;

			// Helpers
			Motion();
			Motion(GameObject*);
			Motion(Motion*);
			~Motion();

			virtual void RefreshTargetComponentsList();
			virtual void Update();
			virtual Motion* Clone();

		private:
			// Target component
			Transform* transform_;

			void SimpleResolve();
			void ServoResolve();
	};
}

#endif //GAME_CORE_ENTITY_SYSTEM_MOTION_HPP
