#include "random.hpp"
#include "component/transform.hpp"
#include "component/ai/random.hpp"
#include "messaging/concrete_messages/intent_message.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	RandomAISystem::RandomAISystem() : System(){
		Require<Transform, RandomAI>();
	}

	RandomAISystem::~RandomAISystem(){}

	void RandomAISystem::OnUpdate(Entity e){
		IntentMessage msg;
		msg.intent = Intent::WALK;
		msg.direction = glm::vec3(1.f, 0.f, 0.f);
		msg.dest = e;

		MessageBus::Push(msg);
	}
}
