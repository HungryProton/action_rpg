#ifndef GAME_CORE_SERVICES_RENDER_HPP
#define GAME_CORE_SERVICES_RENDER_HPP

#include "tools/opengl.hpp" 

namespace game{

    class Render{

        public:
            Render();
            ~Render();

            GLFWwindow* GetWindow();

        private:
            void InitializeOpenGL();
            void InitializeGLFW();

            GLFWwindow* window_;
    };
}

#endif // GAME_CORE_SERVICES_RENDER_HPP
