#include "core/game/game.hpp"
#include "input.hpp"
#include "core/locator/locator.hpp"
#include "core/service/render/render.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

namespace game{

    Input::Input(){}

    Input::~Input(){
        this->ClearMemory();
    }

    void Input::Initialize(GLFWwindow* window){
        this->window_ = window;
    }

    void Input::ClearMemory(){

    }

    void Input::Update(){
        glfwPollEvents();

        InputMessage msg;

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

    }
}
