#ifndef GAME_CORE_SERVICES_RENDER_HPP
#define GAME_CORE_SERVICES_RENDER_HPP

#include <map>
#include <typeindex>
#include "tools/opengl.hpp" 
#include "core/services/service.hpp"

namespace game{

    class Render : public Service{

        public:
            Render();
            ~Render();

            void Update();
            GLFWwindow* GetWindow();

        private:
            void InitializeHelpers();
            void InitializeOpenGL();
            void InitializeGLFW();

            template<class T>
            void RegisterHelper();

            GLFWwindow* window_;
            std::multimap<std::type_index, Service*> helpers_;
    };
}

#include "render.tcc"

#endif // GAME_CORE_SERVICES_RENDER_HPP
