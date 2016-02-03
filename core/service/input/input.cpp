#include "core/game/game.hpp"
#include "input.hpp"
#include "core/locator/locator.hpp"
#include "core/service/render/render.hpp"
#include "core/messaging/message_bus.hpp"
#include "core/messaging/concrete_messages/input_message.hpp"

namespace game{

	Input::Input(){
		this->LoadDefaultKeymap();
	}

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

		// TODO : change this to use the messaging system
		if (this->GetKeyStatus(GLFW_KEY_ESCAPE) == KEY_PRESSED){
			Game::Stop();
		}

		for(auto it = this->keymap_.begin(); it != this->keymap_.end(); it++){
			this->SendCommandForKey(it->first, it->second);
		}
	}

	KeyStatus Input::GetKeyStatus(int key_code){
		int glfw_status = glfwGetKey(this->window_, key_code);
		auto pair = this->previous_keys_status_.find(key_code);
		KeyStatus status;

		glfw_status == GLFW_PRESS ? status = KEY_PRESSED : status = KEY_RELEASED;

		// If previous state wasn't stored
		if(pair == this->previous_keys_status_.end()){
			this->previous_keys_status_.insert(std::pair<int, int>(key_code, glfw_status));
			return status;
		}

		// If the status changed, check if it's because key was released
		if(glfw_status != pair->second){
			pair->second = glfw_status;

			if(glfw_status == GLFW_RELEASE){
				status = KEY_JUST_RELEASED;
			}
		}
		return status;
	}

	void Input::SendCommandForKey(int key_code, Command command){
		InputMessage msg;
		msg.status = GetKeyStatus(key_code);
		msg.command = command;
		msg.modifier_pressed = (GetKeyStatus(this->modifier_code) == KEY_PRESSED);

		if(msg.status != KEY_RELEASED){
			MessageBus::Push(msg);
		}
	}

	void Input::LoadDefaultKeymap(){
		this->keymap_.clear();
		AddEntryInKeymap(GLFW_KEY_W, Command::MOVE_UP);
		AddEntryInKeymap(GLFW_KEY_S, Command::MOVE_DOWN);
		AddEntryInKeymap(GLFW_KEY_A, Command::MOVE_LEFT);
		AddEntryInKeymap(GLFW_KEY_D, Command::MOVE_RIGHT);
		AddEntryInKeymap(GLFW_KEY_V, Command::ATTACK);
		this->modifier_code = GLFW_KEY_LEFT_ALT;
	}

	void Input::AddEntryInKeymap(int key_code, Command command){
		this->keymap_.insert(std::pair<int, Command>(key_code, command));
	}
}
