#include "logic.hpp"
#include "core/locator/locator.hpp"
#include "core/service/builder/world_builder.hpp"
#include "core/service/builder/game_object_builder.hpp"
#include "core/game/game.hpp"
#include "tools/random.hpp"

#include "core/component/transform.hpp"
#include "core/component/camera.hpp"
#include "core/component/drawable.hpp"
#include "core/component/texture.hpp"
#include "core/component/animated_texture.hpp"
#include "core/component/input_to_intent.hpp"
#include "core/component/intent_to_motion.hpp"
#include "core/component/motion_to_animation.hpp"
#include "core/component/motion.hpp"
#include "core/component/mesh.hpp"
#include "core/component/constraint.hpp"
#include "core/component/collider.hpp"
#include "core/component/shapes/box.hpp"
#include "core/component/shapes/circle.hpp"
#include "core/component/battle/melee_attack.hpp"
#include "core/component/behavior_controller.hpp"
#include "core/component/particle_emitter.hpp"
#include "core/component/particle.hpp"
#include "core/component/artificial_intelligence/random.hpp"
#include "core/component/health.hpp"
#include "core/component/death_controller.hpp"

namespace game{

	Logic::Logic(){
		Game::RequestForService<GameObjectBuilder>();
	}

	Logic::~Logic(){
		this->ClearMemory();
	}

	void Logic::Initialize(){

		SpawnMultipleSprite("../data/characters/female/animated/female_1.txt", 15);
		SpawnMultipleSprite("../data/characters/female/animated/female_2.txt", 15);
		SpawnMultipleSprite("../data/characters/female/animated/female_3.txt", 15);
		GameObject* camera = SpawnCamera(glm::vec3(0, -20, 12));
		GameObject* house = SpawnMesh("../data/environment/architecture/building/house_01/house01.obj");
		new Box(8, 8, house);

		GameObject* player = SpawnPlayer("../data/characters/female/animated/female_1.txt");
		SpawnRandomMeshes("../data/environment/terrain/vegetation/tree.obj", 15, 0.5f);
		SpawnRandomMeshes("../data/environment/terrain/vegetation/bush.obj", 10, 0.35f);
		SpawnRandomMeshes("../data/environment/terrain/rock/rock_01.obj", 8, 1.f);
		SpawnRandomMeshes("../data/environment/terrain/rock/rock_02.obj", 8, 1.f);

		SpawnPillar();

		TerrainBuilder terrain_builder;
		terrain_builder.SetMapSize(60, 60);
		GameObject* terrain = terrain_builder.GenerateTerrain();
		this->game_objects_.push_back(terrain);

		Constraint* c = new Constraint(camera);
		c->type = ConstraintType::COPY;
		c->soft_resolve = false;
		c->value = &(camera->GetComponent<Camera>()->target);
		c->target_value = &(player->GetComponent<Transform>()->position);

		Constraint* c2 = new Constraint(camera);
		c2->type = ConstraintType::KEEP_OFFSET;
		if(camera->GetComponent<Transform>() == nullptr){
			LOG(ERROR) << "Camera has no transform" << std::endl;
		}
		c2->SetOffset( &(camera->GetComponent<Transform>()->position),
									&(player->GetComponent<Transform>()->position) );

	}

	void Logic::ClearMemory(){
		for(unsigned int i = 0; i < this->game_objects_.size(); i++){
			GameObject* g = this->game_objects_[i];
			this->game_objects_.erase(this->game_objects_.begin() + i);
			delete g;
		}
	}

	void Logic::Update(){
		for(GameObject* game_object : this->game_objects_){
			game_object->Update();
		}
	}

	GameObject* Logic::SpawnSprite(std::string file_path, glm::vec3 position){
		GameObject* sprite = new GameObject();
		Transform* t = new Transform(sprite);
		t->position = position;
		new AnimatedTexture(file_path, sprite);
		new Drawable(sprite);
		new Circle(0.35f, sprite);
		new Motion(sprite);

		BehaviorController* b = new BehaviorController(sprite);

		new RandomAi(sprite);

		b->AddAction(new DeathController(sprite), 10);
		b->AddAction(new IntentToMotion(sprite), 30);
		b->AddAction(new MotionToAnimation(sprite), 40);

		Collider* collider = new Collider(sprite);
		collider->shape_type = std::type_index(typeid(Circle));
		new Health(sprite);
		this->game_objects_.push_back(sprite);
		return sprite;
	}

	void Logic::SpawnMultipleSprite(std::string file_path, int count){
		for(int i = 0; i < count; i++){
			glm::vec3 position;
			position.x = 10 - Random::NextFloat(20);
			position.y = 10 - Random::NextFloat(20);
			position.z = 0;
			SpawnSprite(file_path, position);
		}
	}

	GameObject* Logic::SpawnPlayer(std::string resource_path){
		GameObject* player = new GameObject();

		new Transform(player);
		new AnimatedTexture(resource_path, player);
		new Drawable(player);
		new Circle(0.35f, player);
		Collider* collider = new Collider(player);
		collider->shape_type = std::type_index(typeid(Circle));
		new Motion(player);
		new InputToIntent(player);

		BehaviorController* b = new BehaviorController(player);

		MeleeAttack* m = new MeleeAttack(player);
		m->animation_name = "attack";
		m->damage_modifier = 2;
		m->attacks_durations.push_back(7);
		m->attacks_durations.push_back(10);
		m->attacks_durations.push_back(13);

		b->AddAction(new IntentToMotion(player), 30);
		b->AddAction(m, 40);
		b->AddAction(new MotionToAnimation(player), 50);

		this->game_objects_.push_back(player);

		return player;
	}

	GameObject* Logic::SpawnMesh(std::string file_path){
		GameObject* mesh = new GameObject();
		Transform* transform = new Transform(mesh);
		transform->position.x = -10;
		transform->position.y = 20;
		//transform->scale /= 2;
		//transform->rotation.z = (-3.1415/2);
		new Mesh(file_path, mesh);
		new Drawable(mesh);
		Collider* collider = new Collider(mesh);
		collider->shape_type = std::type_index(typeid(Box));
		collider->SetMass(0);
		this->game_objects_.push_back(mesh);
		return mesh;
	}

	void Logic::SpawnRandomMeshes(std::string file_path, int count, float size){
		for(int i = 0; i < count; i++){
			GameObject* m = SpawnMesh(file_path);
			Transform* t = m->GetComponent<Transform>();
			t->position.x = 15 - Random::NextFloat(30);
			t->position.y = 15 - Random::NextFloat(30);
			t->rotation.z = Random::NextFloat(360)*(3.1415/180.f);
			new Circle(size, m);
			Collider* c = m->GetComponent<Collider>();
			c->shape_type = std::type_index(typeid(Circle));
		}
	}

	GameObject* Logic::SpawnPillar(){
		GameObject* pillar = SpawnMesh("../data/environment/terrain/misc/respawn_pillar.obj");

		Transform* t = pillar->GetComponent<Transform>();
		t->position.x = 10 - Random::NextFloat(20);
		t->position.y = 10 - Random::NextFloat(20);
		t->rotation.z = Random::NextFloat(360)*(3.1415/180.f);
		new Circle(0.6f, pillar);
		Collider* c = pillar->GetComponent<Collider>();
		c->shape_type = std::type_index(typeid(Circle));

		ParticleEmitter* pe = new ParticleEmitter(pillar);
		GameObject* particle = new GameObject();
		new Transform(particle);
		new Texture("../data/environment/terrain/misc/spark.png", particle);
		new Drawable(particle);
		new Particle(particle);

		pe->SetParticle(particle);
		pe->min_duration = 2.f;
		pe->max_duration = 6.f;
		pe->speed = 2.f;
		pe->min_count = 30;
		pe->max_count = 50;

		return pillar;
	}

	GameObject* Logic::SpawnCamera(glm::vec3 position){
		GameObject* camera = new GameObject();
		Transform* t = new Transform(camera);
		t->position = position;
		Camera* cam = new Camera(camera);
		cam->SetActive();
		new Motion(camera);
		this->game_objects_.push_back(camera);
		return camera;
	}
}
