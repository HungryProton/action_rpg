#ifndef GAME_CORE_MESSAGING_AUDIO_COMMAND_HPP
#define GAME_CORE_MESSAGING_AUDIO_COMMAND_HPP

#include "../message.hpp"

namespace game{


	enum class AudioAction{
		PLAY,
		PAUSE,
		RESUME,
		STOP
	};

	struct AudioCommand : public Message{
		AudioAction action;
	};
}
#endif //GAME_CORE_MESSAGING_AUDIO_COMMAND_HPP
