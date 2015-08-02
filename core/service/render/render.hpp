#ifndef GAME_CORE_SERVICES_RENDER_HPP
#define GAME_CORE_SERVICES_RENDER_HPP

#include <vector>
#include <typeindex>
#include "tools/opengl.hpp" 
#include "core/service/service.hpp"

// -- Helpers inclusions
#include "core/service/helper/image_helper.hpp"

namespace game{

    class Render : public Service{

        public:
            Render();
            ~Render();

            void ClearMemory();
            void Update();

            GLFWwindow* GetWindow();

        private:
            void InitializeHelpers();
            void InitializeOpenGL();
            void InitializeGLFW();

            template<class T>
            void RegisterHelper();

            GLFWwindow* window_;
    };
}

#include "render.tcc"

#endif // GAME_CORE_SERVICES_RENDER_HPP
