#ifndef GAME_CORE_ENTITY_SYSTEM_INPUT_TO_MOTION_HPP
#define GAME_CORE_ENTITY_SYSTEM_INPUT_TO_MOTION_HPP

#include "core/entity/system/system.hpp"

namespace game{

	class InputToMotion : public System{
		public:
			InputToMotion();
			InputToMotion(GameObject*);
			InputToMotion(InputToMotion*);

			virtual void RefreshTargetComponentsList();
			virtual void Update();
			virtual InputToMotion* Clone();
		private:

	};
}

#endif //GAME_CORE_ENTITY_SYSTEM_INPUT_TO_MOTION_HPP
