#include "world.hpp"

#include "ecs/ecs.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"
#include "component/texture.hpp"
#include "component/drawable.hpp"
#include "component/mesh.hpp"
#include "component/light/point.hpp"
#include "component/action/player_controllable.hpp"
#include "component/action/simple_motion.hpp"
#include "component/ai/random.hpp"
#include "component/constraint.hpp"

#include "messaging/concrete_messages/rendering_intent.hpp"
#include "messaging/message_bus.hpp"
#include "module/architecture/architecture_module.hpp"

namespace game{

	void SpawnBasicEntities_tmp(){
		Entity camera = ecs::CreateEntity();
		Transform* cam_t = ecs::CreateComponent<Transform>(camera);
		Camera* cam = ecs::CreateComponent<Camera>(camera);
		cam_t->position = glm::vec3(0, -10, 8);

		RenderingIntent msg;
		msg.id = 1;
		msg.from = camera;
		msg.action = RIntent::SET_ACTIVE_CAMERA;
		MessageBus::Push(msg);

		Entity sprite = ecs::CreateEntity();
		Transform* sprite_t = ecs::CreateComponent<Transform>(sprite);
		ecs::CreateComponent<Texture>(sprite, "../data/characters/female/single_idle.png");
		ecs::CreateComponent<Drawable>(sprite)->type = DrawableType::SPRITE;
		ecs::CreateComponent<PointLight>(sprite);
		ecs::CreateComponent<PlayerControllable>(sprite);
		ecs::CreateComponent<SimpleMotion>(sprite)->speed = 10.f;

		Constraint* c = ecs::CreateComponent<Constraint>(camera);
		c->type = ConstraintType::KEEP_OFFSET;
		c->SetOffset(&(cam_t->position), &(sprite_t->position));

		Constraint* c2 = ecs::CreateComponent<Constraint>(camera);
		c2->type = ConstraintType::COPY;
		c2->value = &(cam->target);
		c2->target_value = &(sprite_t->position);

		Entity pnj = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(pnj)->position.x = -5;
		ecs::CreateComponent<Texture>(pnj, "../data/characters/female/single_idle.png");
		ecs::CreateComponent<Drawable>(pnj)->type = DrawableType::SPRITE;
		ecs::CreateComponent<SimpleMotion>(pnj)->speed = 1.f;
		ecs::CreateComponent<RandomAI>(pnj);

		for(int i = 0; i < 5; i++){
			Entity light = ecs::CreateEntity();

			Transform* t = ecs::CreateComponent<Transform>(light);
			t->position.x = 4 - Random::NextFloat()*8;
			t->position.y = 4 - Random::NextFloat()*8;
			t->position.z = .5f + Random::NextFloat()*2;

			PointLight* pl = ecs::CreateComponent<PointLight>(light);
			pl->power = Random::NextFloat(3);
			pl->color.x = Random::NextFloat();
			pl->color.y = Random::NextFloat();
			pl->color.z = Random::NextFloat();

			ecs::CreateComponent<Drawable>(light);
		}


		Entity plate = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(plate);
		ecs::CreateComponent<Mesh>(plate)->LoadFromFile("../data/floor.obj");
		ecs::CreateComponent<Drawable>(plate, DrawableType::MESH);
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
