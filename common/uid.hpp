#ifndef GAME_COMMON_UID_GENERATOR_HPP
#define GAME_COMMON_UID_GENERATOR_HPP

namespace game{

	class Uid{
		public:
			static long int Next();

		private:
			static long int last_;
	};

}
#endif //GAME_COMMON_UID_GENERATOR_HPP

