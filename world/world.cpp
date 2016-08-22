#include "world.hpp"

#include "ecs/ecs.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"
#include "component/texture.hpp"
#include "component/drawable.hpp"
#include "component/mesh.hpp"

#include "messaging/concrete_messages/rendering_intent.hpp"
#include "messaging/message_bus.hpp"
#include "module/architecture/architecture_module.hpp"

namespace game{

	void SpawnBasicEntities_tmp(){
		Entity camera = ecs::CreateEntity();
		Transform* t = ecs::CreateComponent<Transform>(camera);
		ecs::CreateComponent<Camera>(camera);
		t->position = glm::vec3(0, -10, 6);

		RenderingIntent msg;
		msg.id = 1;
		msg.from = camera;
		msg.action = RIntent::SET_ACTIVE_CAMERA;
		MessageBus::Push(msg);

		Entity sprite = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(sprite);
		ecs::CreateComponent<Texture>(sprite, "../data/characters/female/single_idle.png");
		ecs::CreateComponent<Drawable>(sprite)->type = DrawableType::SPRITE;


		/*Entity scorpio = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(scorpio)->rotation.z = 45;
		ecs::CreateComponent<Mesh>(scorpio)->LoadFromFile("../data/test.obj");
		ecs::CreateComponent<Drawable>(scorpio, DrawableType::MESH);
		*/
	}

	void SpawnBuildings(double seed){
		ArchitectureModule module;
		module.Generate(seed);
	}

	void World::Initialize(double seed){
		seed_ = seed;

		// Add a bunch of module that do following things:
		// Load bunch of paramters maybe ?
		// Generate the map somehow
		// Fill the map with objects, people, ennemies and so on
		// Add story-related stuff and procedural narrative
		// Spawn the player somewhere

		SpawnBasicEntities_tmp();
		SpawnBuildings(seed);
	}

	void World::GenerateNew(){

	}

	void World::LoadFromFile(){

	}

	void World::SaveToFile(std::string save_name){
		LOG(INFO) << "Saving game to " << save_name<< ".save" << std::endl;
	}

	double World::seed_;
}
