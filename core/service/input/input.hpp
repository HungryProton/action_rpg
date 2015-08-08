#ifndef GAME_CORE_SERVICE_INPUT_HPP
#define GAME_CORE_SERVICE_INPUT_HPP

#include <vector>
#include "core/service/service.hpp"
#include "core/messaging/input_message.hpp"
#include "tools/opengl.hpp"

namespace game{
    
    class Input : public CoreService{
        public:
            Input();
            ~Input();

            void Initialize(GLFWwindow*);
            void ClearMemory();
            void Update();
            void RegisterListener(IMessageHandler*);

        private:
            void LoadKeymapFromFile(std::string);
            void SendMessageToListeners(InputMessage);

            std::vector<IMessageHandler*> listeners_;
            GLFWwindow* window_;
    };
}

#endif //GAME_CORE_SERVICE_INPUT_HPP
