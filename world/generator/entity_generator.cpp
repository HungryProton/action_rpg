#include "entity_generator.hpp"
#include "entity/entity_factory.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "messaging/message_bus.hpp"

namespace game{

	EntityGenerator::EntityGenerator(){}

	EntityGenerator::~EntityGenerator(){}

	unsigned long EntityGenerator::SpawnPlayer(){
		unsigned long player = EntityFactory::CreateFromPreset("player");
		// Apply some rules on player here (positionning, weapons etc)
		return player;
	}

	unsigned long EntityGenerator::SpawnCamera(){
		unsigned long camera = EntityFactory::CreateFromPreset("camera");
		RenderingIntent msg;
		msg.from_id = camera;
		msg.action = RIntent::SET_ACTIVE_CAMERA;
		MessageBus::Push(msg);
		return camera;
	}
}
