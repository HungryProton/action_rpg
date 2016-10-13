#include "input.hpp"
#include "messaging/message_bus.hpp"
#include "messaging/concrete_messages/input_message.hpp"

namespace game{

	Input::Input(){
		this->LoadDefaultKeymap();
	}

	Input::~Input(){

	}

	void Input::Initialize(GLFWwindow* window){
		this->window_ = window;
		DefineCursorParameters(window);
	}

	void Input::BeforeUpdate(){
		glfwPollEvents();

		for(auto it = this->keymap_.begin(); it != this->keymap_.end(); it++){
			this->SendCommandForKey(it->first, it->second);
		}

	}

	KeyStatus Input::GetKeyStatus(int key_code){
		int glfw_status = glfwGetKey(this->window_, key_code);
		auto pair = this->previous_keys_status_.find(key_code);
		KeyStatus status;

		glfw_status == GLFW_PRESS ? status = KeyStatus::PRESSED : status = KeyStatus::RELEASED;

		// If previous state wasn't stored
		if(pair == this->previous_keys_status_.end()){
			this->previous_keys_status_.insert(std::pair<int, int>(key_code, glfw_status));
			return status;
		}

		// If the status changed, check if it's because key was released
		if(glfw_status != pair->second){
			pair->second = glfw_status;

			if(glfw_status == GLFW_RELEASE){
				status = KeyStatus::JUST_RELEASED;
			}
		}
		return status;
	}

	void Input::SendCommandForKey(int key_code, Command command){
		InputMessage msg;
		msg.status = GetKeyStatus(key_code);
		msg.command = command;
		msg.first_modifier_pressed = (GetKeyStatus(this->first_modifier_code) == KeyStatus::PRESSED);
		msg.second_modifier_pressed = (GetKeyStatus(this->second_modifier_code) == KeyStatus::PRESSED);

		if(msg.status != KeyStatus::RELEASED){
			MessageBus::Push(msg);
		}
	}

	void Input::LoadDefaultKeymap(){
		this->keymap_.clear();
		AddEntryInKeymap(GLFW_KEY_W, Command::UP);
		AddEntryInKeymap(GLFW_KEY_S, Command::DOWN);
		AddEntryInKeymap(GLFW_KEY_A, Command::LEFT);
		AddEntryInKeymap(GLFW_KEY_D, Command::RIGHT);
		AddEntryInKeymap(GLFW_KEY_V, Command::ATTACK);
		AddEntryInKeymap(GLFW_KEY_ESCAPE, Command::RETURN);
		this->first_modifier_code = GLFW_KEY_LEFT_SHIFT;
		this->second_modifier_code = GLFW_KEY_LEFT_ALT;
	}

	void Input::AddEntryInKeymap(int key_code, Command command){
		this->keymap_.insert(std::pair<int, Command>(key_code, command));
	}

	void Input::DefineCursorParameters(GLFWwindow* window){
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPosCallback(window, Input::OnCursorMove);
	}

	void Input::OnCursorMove(GLFWwindow*, double x, double y){
		InputMessage msg;
		msg.command = Command::TARGET;
		msg.position = glm::vec2(x, y);
		MessageBus::Push(msg);
	}
}
