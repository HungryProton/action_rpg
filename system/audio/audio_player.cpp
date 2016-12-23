#include "audio_player.hpp"
#include "component/transform.hpp"
#include "component/audio/audio.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace game{

	AudioPlayer::AudioPlayer() : System(){
		Require<Transform, Audio>();
		initialized_ = false;
		InitializeAudioContext();
	}

	AudioPlayer::~AudioPlayer(){}

	void AudioPlayer::InitializeAudioContext(){
		ALCdevice* device = alcOpenDevice(NULL); //Get prefered device
		if(!device){ return; }

		ALCcontext* context = alcCreateContext(device, NULL);
		if(!context){ return; }

		if(!alcMakeContextCurrent(context)){ return; }
		initialized_ = true;
	}

	void AudioPlayer::DestroyAudioContext(){
		ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);

		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	void AudioPlayer::BeforeUpdate(){
		this->MessageHandler<AudioCommand>::PollMessages();
	}

	void AudioPlayer::OnUpdate(Entity){
		if(!initialized_){ return; }
	}

	void AudioPlayer::OnMessage(AudioCommand){
		if(!initialized_){ return; }

	}

}
