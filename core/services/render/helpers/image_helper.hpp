#ifndef GAME_SERVICE_IMAGE_HELPER_HPP
#define GAME_SERVICE_IMAGE_HELPER_HPP

#include <map>
#include "core/services/service.hpp"
#include "image.hpp"

namespace game{

    class ImageHelper : public Service{
        public:
            ImageHelper();
            ~ImageHelper();

        private:
            std::map<std::string, Image*> images_;
    };
}

#endif //GAME_SERVICE_IMAGE_HELPER_HPP
