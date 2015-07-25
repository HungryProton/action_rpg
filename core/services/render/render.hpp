#ifndef GAME_CORE_SERVICES_RENDER_HPP
#define GAME_CORE_SERVICES_RENDER_HPP

#include <vector>
#include <typeindex>
#include "tools/opengl.hpp" 
#include "core/services/service.hpp"

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
            std::vector<Service*> helpers_;
    };
}

#include "render.tcc"

#endif // GAME_CORE_SERVICES_RENDER_HPP
