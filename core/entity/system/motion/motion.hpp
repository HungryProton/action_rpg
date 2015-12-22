#ifndef GAME_CORE_ENTITY_SYSTEM_MOTION_HPP
#define GAME_CORE_ENTITY_SYSTEM_MOTION_HPP

#include "core/entity/system/system.hpp"
#include "core/entity/component/transform.hpp"
#include <glm/glm.hpp>

namespace game{

	enum MotionType{SIMPLE, SERVO_CONTROL};

	class Motion : public System{
		public:
			Motion();
			Motion(GameObject*);
			~Motion();

			virtual void RefreshTargetComponentsList();
			virtual void Update();

			void SetMotionType(MotionType);
			MotionType GetMotionType();

		private:
			MotionType type_;
			glm::vec3 direction_;
			glm::vec3 rotation_;
			glm::vec3 scale_;
			glm::vec3 max_force_;

			// Target component
			Transform* transform_;

			void SimpleResolve();
			void ServoResolve();
	};
}

#endif //GAME_CORE_ENTITY_SYSTEM_MOTION_HPP
