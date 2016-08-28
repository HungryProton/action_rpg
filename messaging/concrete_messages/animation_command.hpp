#ifndef GAME_CORE_MESSAGING_ANIMATION_COMMAND_HPP
#define GAME_CORE_MESSAGING_ANIMATION_COMMAND_HPP

#include <string>
#include "../message.hpp"
#include "component/common.hpp"

namespace game{

	enum class AnimationAction{PLAY, PAUSE, STOP};

	struct AnimationCommand : public Message{
		AnimationAction action;
		std::string name;
		int offset;
		Direction direction;
		bool loop;

		AnimationCommand(){
			direction = Direction::LAST;
			loop = false;
			offset = 0;
		}
	};
}

#endif //GAME_CORE_MESSAGING_ANIMATION_COMMAND_HPP
