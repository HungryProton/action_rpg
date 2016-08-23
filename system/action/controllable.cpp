#include "controllable.hpp"
#include "component/action/player_controllable.hpp"

namespace game{

	Controllable::Controllable() : System(){
		Require<PlayerControllable>();
	}

	Controllable::~Controllable(){}

	void Controllable::BeforeUpdate(){
		this->MessageHandler<InputMessage>::PollMessages();
	}

	void Controllable::OnUpdate(Entity entity){

	}

	void Controllable::OnMessage(InputMessage msg){

	}
}
