#include "follow_pointer.hpp"
#include "component/common.hpp"

namespace game{

	FollowPointer::FollowPointer() : System(){
		Require<FollowPointer, Direction>();
	}

	FollowPointer::~FollowPointer(){ }

	void FollowPointer::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void FollowPointer::OnMessage(IntentMessage msg){
		if(glm::length(msg.target_direction) == 0){ return; }
		Direction d = GetDirectionFromVector(msg.target_direction);

	}
}
