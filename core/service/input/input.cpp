#include "core/service/input/input.hpp"

namespace game{
    
    Input::Input(){}

    Input::~Input(){
        this->ClearMemory();
    }

    void Input::ClearMemory(){
        this->listeners_.clear();
    }

    void Input::Update(){

        glfwPollEvents();

        Message msg;
        msg.subject = EMPTY;

        // Move backward
        if (glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            Game::Quit();
        }

        SendMessageToListeners(msg);
    }

     void Input::RegisterListener(System* listener){
        this->listeners_.push_back(listener);
    }
}
