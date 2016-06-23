#include "entity_generator.hpp"
#include "ecs/entity_factory.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "messaging/message_bus.hpp"
#include "component/transform.hpp"
#include "ecs/entity.hpp"
#include "common/random.hpp"
#include "component/texture.hpp"
#include "system/renderer/renderer.hpp"
#include "ecs/system_register.hpp"

namespace game{

	EntityGenerator::EntityGenerator(){}

	EntityGenerator::~EntityGenerator(){}

	Entity EntityGenerator::SpawnPlayer(){
		Entity player = EntityFactory::CreateFromPreset("player");
		// Apply some rules on player here (positionning, weapons etc)
		return player;
	}

	Entity EntityGenerator::SpawnRandom(){
		Entity e = Entity::Create();
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

	Entity EntityGenerator::SpawnCamera(){
		Entity camera = EntityFactory::CreateFromPreset("camera");
		RenderingIntent msg;
		msg.from_id = camera;
		msg.action = RIntent::SET_ACTIVE_CAMERA;
		MessageBus::Push(msg);
		return camera;
	}
}
