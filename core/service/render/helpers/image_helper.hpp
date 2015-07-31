#ifndef GAME_SERVICE_IMAGE_HELPER_HPP
#define GAME_SERVICE_IMAGE_HELPER_HPP

#include <map>
#include "core/service/service.hpp"
#include "image.hpp"

namespace game{

    class ImageHelper : public Service{
        public:
            ImageHelper();
            ~ImageHelper();

            void ClearMemory();
            Image* LoadFromFile(std::string);

        private:
            Image* GetAlreadyLoadedImage(std::string);

            std::map<std::string, Image*> images_;
    };
}

#endif //GAME_SERVICE_IMAGE_HELPER_HPP
