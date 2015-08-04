#include "game.hpp"
#include "input.hpp"

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

        InputMessage msg;
        msg.subject = EMPTY;

        // Move backward
        if (glfwGetKey( this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            Game::Stop();
        }

        SendMessageToListeners(msg);
    }

    void Input::RegisterListener(IMessageHandler* listener){
        this->listeners_.push_back(listener);
    }

    void Input::SendMessageToListeners(InputMessage message){
        for( auto listener : this->listeners_ ){
            message.Dispatch( listener );
        }
    }

}
