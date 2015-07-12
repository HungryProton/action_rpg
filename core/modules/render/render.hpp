#ifndef GAME_CORE_MODULE_RENDER_HPP
#define GAME_CORE_MODULE_RENDER_HPP

#include "core/modules/base/module.hpp"
#include "tools/message.hpp"
#include "tools/opengl.hpp"

namespace game{

    class Render : public Module {
        public:
            Render();
            ~Render();

            void HandleMessage(Message msg);

        private:
            void Run();

            void Update();

            void CreateWindow();
            
            void InitializeOpenGL();

            bool LoadParametersFromFile(std::string file_path);

            void ClearScreen();


            GLFWwindow* window_;

            // Graphics parameters
            const char* game_name_;
            int opengl_major_version_;
            int opengl_minor_version_;
            int antialiasing_level_; 
            int x_resolution_;
            int y_resolution_;
    };
}

#endif // GAME_CORE_MODULE_RENDER_HPP
