#include "entity_generator.hpp"
#include "entity/entity_factory.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "messaging/message_bus.hpp"
#include "component/transform.hpp"
#include "entity/entity.hpp"
#include "common/random.hpp"
#include "component/texture.hpp"
#include "system/renderer/renderer.hpp"
#include "entity/system_register.hpp"

namespace game{

	EntityGenerator::EntityGenerator(){}

	EntityGenerator::~EntityGenerator(){}

	unsigned long EntityGenerator::SpawnPlayer(){
		unsigned long player = EntityFactory::CreateFromPreset("player");
		// Apply some rules on player here (positionning, weapons etc)
		return player;
	}

	unsigned long EntityGenerator::SpawnRandom(){
		unsigned long e = Entity::Create();
		Transform* t = new Transform(e);
		new Texture("../data/characters/female/single.png", e);
		Drawable* d = new Drawable(e);
		d->type = DrawableType::SPRITE;
		SystemRegister::AssociateEntityTo<Renderer>(e);
		t->position.x = 3 - Random::NextFloat(6);
		t->position.y = 3 - Random::NextFloat(6);
		t->position.z = 0;
		return e;
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
