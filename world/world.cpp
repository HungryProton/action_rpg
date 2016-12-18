#include "world.hpp"
#include "ecs/ecs.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"
#include "component/graphic/texture.hpp"
#include "component/graphic/drawable.hpp"
#include "component/graphic/mesh.hpp"
#include "component/light/point.hpp"
#include "component/light/directional.hpp"
#include "component/input/player_controllable.hpp"
#include "component/motion.hpp"
#include "component/ai/random.hpp"
#include "component/constraint.hpp"
#include "component/graphic/atlas.hpp"
#include "component/action/walk_run.hpp"
#include "component/action/dodge.hpp"
#include "component/item/pickup.hpp"
#include "component/collider.hpp"
#include "component/shapes/circle.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "messaging/message_bus.hpp"
#include "module/architecture/architecture_module.hpp"
#include "component/action/follow_pointer.hpp"
#include "component/action/behavior.hpp"
#include "component/item/equipment_slot.hpp"

namespace game{

	void SpawnMesh(std::string, int, float);

	void SpawnBasicEntities_tmp(){
		Entity camera = ecs::CreateEntity();
		Transform* cam_t = ecs::CreateComponent<Transform>(camera);
		Camera* cam = ecs::CreateComponent<Camera>(camera);
		cam_t->position = glm::vec3(0, -5, 12);

		RenderingIntent msg;
		msg.id = 1;
		msg.from = camera;
		msg.action = RIntent::SET_ACTIVE_CAMERA;
		MessageBus::Push(msg);

		Entity sprite = ecs::CreateEntity();
		Transform* sprite_t = ecs::CreateComponent<Transform>(sprite, glm::vec3(0, 10, 0));
		//ecs::CreateComponent<Drawable>(sprite)->type = DrawableType::SPRITE;
		ecs::CreateComponent<Atlas>(sprite, "../data/characters/female/body/f_body.txt");
		ecs::CreateComponent<PlayerControllable>(sprite);
		ecs::CreateComponent<Motion>(sprite);
		ecs::CreateComponent<Behavior>(sprite);
		ecs::CreateComponent<WalkRun>(sprite, 1.f, 6.f);
		ecs::CreateComponent<Dodge>(sprite);
		Collider* sc = ecs::CreateComponent<Collider>(sprite);
		sc->SetMass(60.f);
		sc->shape_type = Shape::CIRCLE;
		ecs::CreateComponent<Circle>(sprite)->radius = 0.35;
		ecs::CreateComponent<FollowPointer>(sprite);

		Entity player_base = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(player_base);
		ecs::CreateComponent<Drawable>(player_base)->type = DrawableType::SPRITE;
		ecs::CreateComponent<Atlas>(player_base, "../data/characters/female/body/f_body.txt");

		Entity player_hair = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(player_hair);
		ecs::CreateComponent<Drawable>(player_hair)->type = DrawableType::SPRITE;
		ecs::CreateComponent<Atlas>(player_hair, "../data/characters/female/hair/long_02/long_hair_02.txt");

		Entity player_armor = ecs::CreateEntity();
		ecs::CreateComponent<Transform>(player_armor);
		ecs::CreateComponent<Drawable>(player_armor)->type = DrawableType::SPRITE;
		ecs::CreateComponent<Atlas>(player_armor, "../data/characters/female/clothes/01/clothes_01.txt");

		EquipmentSlot* base = ecs::CreateComponent<EquipmentSlot>(sprite, EquipmentType::BODY);
		base->Equip(player_base);
		EquipmentSlot* equipment = ecs::CreateComponent<EquipmentSlot>(sprite, EquipmentType::HEAD);
		equipment->Equip(player_hair);
		EquipmentSlot* equipment2 = ecs::CreateComponent<EquipmentSlot>(sprite, EquipmentType::ARMOR);
		equipment2->Equip(player_armor);

		Entity light = ecs::CreateEntity();
		ecs::CreateComponent<DirectionalLight>(light, glm::vec3(-5, 5, -5), 0.8);
		ecs::CreateComponent<Drawable>(light);


		Constraint* c = ecs::CreateComponent<Constraint>(camera);
		c->type = ConstraintType::KEEP_OFFSET;
		c->SetOffset(&(cam_t->position), &(sprite_t->position));
		c->name = "Camera, keep offset wth target";

		Constraint* c2 = ecs::CreateComponent<Constraint>(camera);
		c2->type = ConstraintType::COPY;
		c2->value = &(cam->target);
		c2->target_value = &(sprite_t->position);
		c->name = "Camera, copy target from player position";

		for(int i = 0; i < 10; i++){
			Entity pnj = ecs::CreateEntity();
			Transform* pnj_t = ecs::CreateComponent<Transform>(pnj);
			ecs::CreateComponent<Texture>(pnj, "../data/characters/female/single_idle.png");
			ecs::CreateComponent<Drawable>(pnj)->type = DrawableType::SPRITE;
			ecs::CreateComponent<Motion>(pnj)->target_speed = 1.f;
			ecs::CreateComponent<RandomAI>(pnj);
			ecs::CreateComponent<WalkRun>(pnj);

			pnj_t->position.x = -Random::NextFloat(5);
			pnj_t->position.y = 5 - Random::NextFloat(10);
		}

		for(int i = 0; i < 0; i++){
			Entity light = ecs::CreateEntity();

			Transform* t = ecs::CreateComponent<Transform>(light);
			t->position.x = 4 - Random::NextFloat()*8.f;
			t->position.y = 4 - Random::NextFloat()*8.f;
			t->position.z = .5f + Random::NextFloat()*2.f;

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

		Entity item = ecs::CreateEntity();
		ecs::CreateComponent<PickUp>(item, EquipmentType::WEAPON, true);
		ecs::CreateComponent<Texture>(item, "../data/item/weapon/melee/sword01.png");
		ecs::CreateComponent<Transform>(item, glm::vec3(-6, 4, 0));
		ecs::CreateComponent<Drawable>(item, DrawableType::SPRITE);
		Collider* item_collider = ecs::CreateComponent<Collider>(item);
		item_collider->sensor = true;
		item_collider->SetMass(1.f);
		item_collider->shape_type = Shape::CIRCLE;
		ecs::CreateComponent<Circle>(item)->radius = 0.1;

		SpawnMesh("../data/environment/terrain/vegetation/bush.obj", 10, 0.2);
		SpawnMesh("../data/environment/terrain/vegetation/tree.obj", 10, 0.2);
		SpawnMesh("../data/environment/terrain/rock/rock_01.obj", 5, 1.1);
		SpawnMesh("../data/environment/terrain/rock/rock_02.obj", 5, 1.1);
	}

	void SpawnBuildings(double seed){
		ArchitectureModule module;
		module.Generate(seed);
	}

	void SpawnMesh(std::string item, int count, float radius){
		for(int i = 0; i < count; i++){

			int x = 10 - Random::NextFloat(20);
			int y = 10 - Random::NextFloat(20);

			Entity e = ecs::CreateEntity();
			ecs::CreateComponent<Transform>(e, glm::vec3(x, y, 0));
			ecs::CreateComponent<Mesh>(e)->LoadFromFile(item);
			Collider* c = ecs::CreateComponent<Collider>(e);
			c->SetMass(0);
			c->shape_type = Shape::CIRCLE;
			ecs::CreateComponent<Circle>(e)->radius = radius;
			ecs::CreateComponent<Drawable>(e)->type = DrawableType::MESH;
		}
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
