#ifndef GAME_CORE_MODULE_RENDER_HPP
#define GAME_CORE_MODULE_RENDER_HPP

#include "core/modules/base/module.hpp"
#include "tools/message.hpp"

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
            void LoadParametersFromFile(std::string file_path);
    };
}

#endif // GAME_CORE_MODULE_RENDER_HPP
