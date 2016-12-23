#ifndef GAME_SERVICE_AUDIO_LOADER_HPP
#define GAME_SERVICE_AUDIO_LOADER_HPP

#include <map>
#include <AL/al.h>
#include <AL/alc.h>
#include "image.hpp"
#include "image_loader.hpp"
#include "service_worker.hpp"

namespace game{

	class AudioLoader : public ServiceWorker{
		public:
			AudioLoader();
			~AudioLoader();

			void ClearMemory();
			ALuint LoadFromFile(std::string);

		private:
			ALuint GetAlreadyLoadedBuffer(std::string);

			std::map<std::string, ALuint> buffers_;
	};
}

#endif //GAME_SERVICE_AUDIO_LOADER_HPP
