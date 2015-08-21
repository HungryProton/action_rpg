#include "core/game/game.hpp"
#include "input.hpp"
#include "core/locator/locator.hpp"
#include "core/service/render/render.hpp"

namespace game{
    
    Input::Input(){}

    Input::~Input(){
        this->ClearMemory();
    }

    void Input::Initialize(GLFWwindow* window){
        this->window_ = window;
    }

    void Input::ClearMemory(){
        this->listeners_.clear();
    }

    void Input::Update(){
        glfwPollEvents();

        InputMessage msg;
        msg.subject = EMPTY;

        if (glfwGetKey( this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            Game::Stop();
        }

        if (glfwGetKey( this->window_, GLFW_KEY_UP) == GLFW_PRESS){
            msg.status = KEY_PRESSED;
            msg.command = MOVE_UP;
        }
        if (glfwGetKey( this->window_, GLFW_KEY_DOWN) == GLFW_PRESS){
            msg.status = KEY_PRESSED;
            msg.command = MOVE_DOWN;
        }
        if (glfwGetKey( this->window_, GLFW_KEY_LEFT) == GLFW_PRESS){
            msg.status = KEY_PRESSED;
            msg.command = MOVE_LEFT;
        }
        if (glfwGetKey( this->window_, GLFW_KEY_RIGHT) == GLFW_PRESS){
            msg.status = KEY_PRESSED;
            msg.command = MOVE_RIGHT;
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
