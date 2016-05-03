#include "gui.hpp"
#include "core/game.hpp"

namespace game{

	Gui::Gui(){ }
	Gui::~Gui(){ }

	void Gui::BeforeUpdate(){
		this->MessageHandler<InputMessage>::UpdateMessages();
	}

	void Gui::OnMessage(InputMessage msg){
		if(msg.command == Command::RETURN){
			Game::Stop();
		}
	}
}
