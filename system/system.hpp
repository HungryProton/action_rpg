#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

namespace game{

	class System{
		public:
			virtual ~System(){};
			virtual void Update() = 0;
	};
}

#endif //GAME_SERVICE_HPP

