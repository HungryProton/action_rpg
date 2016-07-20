#ifndef GAME_SERVICE_IMAGE_LOADER_HPP
#define GAME_SERVICE_IMAGE_LOADER_HPP

#include <map>
#include "image.hpp"
#include "image_loader.hpp"
#include "service_worker.hpp"

namespace game{

	class ImageLoader : public ServiceWorker{
		public:
			ImageLoader();
			~ImageLoader();

			void ClearMemory();
			Image* LoadFromFile(std::string);

		private:
			Image* GetAlreadyLoadedImage(std::string);
			void GenerateOpenGLTexture(Image*);

			std::map<std::string, Image*> images_;
	};
}

#endif //GAME_SERVICE_IMAGE_LOADER_HPP
