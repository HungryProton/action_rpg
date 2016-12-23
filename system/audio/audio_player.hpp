#ifndef GAME_SYSTEM_AUDIO_PLAYER_HPP
#define GAME_SYSTEM_AUDIO_PLAYER_HPP

#include "system/system.hpp"
#include "messaging/concrete_messages/audio_command.hpp"
#include "messaging/message_handler.hpp"

namespace game{

	class AudioPlayer : public System,
											public MessageHandler<AudioCommand>{
		public:
			AudioPlayer();
			~AudioPlayer();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void OnMessage(AudioCommand);

			void InitializeAudioContext();
			void DestroyAudioContext();
			void Play(Entity);
			void Pause(Entity);
			void Stop(Entity);
			void Resume(Entity);

			bool initialized_;
	};
}

#endif //GAME_SYSTEM_AUDIO_PLAYER_HPP
