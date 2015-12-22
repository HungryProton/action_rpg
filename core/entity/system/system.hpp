#ifndef GAME_CORE_SYSTEM_HPP
#define GAME_CORE_SYSTEM_HPP

#include <map>

namespace game{

	class GameObject;
	struct Component;

	class System{
		public:
			System();
			System(GameObject*);
			virtual ~System();

			virtual void RefreshTargetComponentsList() = 0;
			virtual void Update() = 0;
			bool IsAttached();
			void Attach();

		protected:
			GameObject* parent;
			bool attached;
	};
}

#endif // GAME_CORE_SYSTEM_HPP

