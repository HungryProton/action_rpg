#include <iostream>
#include <vector>
#include <sndfile.h>
#include "audio_loader.hpp"
#include "common/logger.hpp"

namespace game{

	AudioLoader::AudioLoader(){

	}

	AudioLoader::~AudioLoader(){
		this->ClearMemory();
	}

	void AudioLoader::ClearMemory(){
		auto it = this->buffers_.begin();
		while(it != this->buffers_.end()){
			alDeleteBuffers(1,&(it->second));
		}
		buffers_.clear();
	}

	ALuint AudioLoader::LoadFromFile(std::string file_path){
		// If Audio was already loaded, return it
		ALuint a = this->GetAlreadyLoadedBuffer(file_path);
		if(a != 0){ return a; }

		// If the Audio wasn't previously loaded, load it now
		SF_INFO file_info;
		SNDFILE* file = sf_open(file_path.c_str(), SFM_READ, &file_info);
		if(!file){
			LOG(WARNING) << "Audio file " << file_path << " does not exists" << std::endl;
			return 0;
		}

		ALsizei nb_samples = static_cast<ALsizei>(file_info.channels * file_info.frames);
		ALsizei sample_rate = static_cast<ALsizei>(file_info.samplerate);

		std::vector<ALshort> samples(nb_samples);
		ALsizei res = sf_read_short(file, &samples[0], nb_samples);
		sf_close(file);

		if(res < nb_samples){ return 0; }
		ALenum format;
		switch(file_info.channels){
			case 1: format = AL_FORMAT_MONO16; break;
			case 2: format = AL_FORMAT_STEREO16; break;
			default: return 0;
		}

		alGenBuffers(1, &a);
		alBufferData(a, format, &samples[0], nb_samples * sizeof(ALushort), sample_rate);
		if(alGetError() != AL_NO_ERROR){ return 0; }

		this->buffers_.insert( std::pair<std::string, ALuint>(file_path, a));
		return a;
	}

	ALuint AudioLoader::GetAlreadyLoadedBuffer(std::string file_path){
		auto it = this->buffers_.find(file_path);

		if(it != this->buffers_.end()){
			return it->second;
		}
		return 0;
	}
}

