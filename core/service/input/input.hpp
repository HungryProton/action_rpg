#ifndef GAME_CORE_SERVICE_INPUT_HPP
#define GAME_CORE_SERVICE_INPUT_HPP

#include <vector>
#include "core/service/service.hpp"
#include "core/entity/system/system.hpp"
#include "tools/opengl.hpp"

namespace game{
    
    class Input : public CoreService{
        public:
            Input();
            ~Input();

            void Initialize(GLFWwindow*);
            void ClearMemory();
            void Update();
            void RegisterListener(System*);

        private:
            void SendMessageToListeners(Message);
            std::vector<System*> listeners_;
            GLFWwindow* window_;
    };
}

#endif //GAME_CORE_SERVICE_INPUT_HPP
