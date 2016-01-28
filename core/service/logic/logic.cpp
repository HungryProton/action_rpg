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
#include "core/component/input_to_motion.hpp"
#include "core/component/motion.hpp"
#include "core/component/mesh.hpp"
#include "core/component/constraint.hpp"

namespace game{

	Logic::Logic(){
		Game::RequestForService<GameObjectBuilder>();
	}

	Logic::~Logic(){
		this->ClearMemory();
	}

	void Logic::Initialize(){

		SpawnMultipleSprite("../data/characters/female/female_1.png", 10);
		SpawnMultipleSprite("../data/characters/female/female_2.png", 10);
		SpawnMultipleSprite("../data/characters/female/female_3.png", 10);
		GameObject* camera = SpawnCamera(glm::vec3(0, -10, 4));
		SpawnMesh("../data/environment/architecture/building/house_01/house01.obj");
		GameObject* player = SpawnPlayer("../data/characters/female/animated/female_1.txt");

		TerrainBuilder terrain_builder;
		terrain_builder.SetMapSize(40, 40);
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
		new Texture(file_path, sprite);
		new Drawable(sprite);
		this->game_objects_.push_back(sprite);
		return sprite;
	}

	void Logic::SpawnMultipleSprite(std::string file_path, int count){
		for(int i = 0; i < count; i++){
			glm::vec3 position;
			position.x = 5 - Random::NextFloat(10);
			position.y = 5 - Random::NextFloat(10);
			position.z = 0;
			SpawnSprite(file_path, position);
		}
	}

	GameObject* Logic::SpawnPlayer(std::string resource_path){
		GameObject* player = new GameObject;
		new Transform(player);
		new Motion(player);
		new InputToMotion(player);
		auto t = new AnimatedTexture(resource_path, player);
		t->Play("walk");
		new Drawable(player);

		this->game_objects_.push_back(player);

		return player;
	}

	GameObject* Logic::SpawnMesh(std::string file_path){
		GameObject* mesh = new GameObject();
		Transform* transform = new Transform(mesh);
		transform->position.y = 5;
		transform->scale /= 2;
		transform->rotation.z = 3*(-3.1415/4);
		new Mesh(file_path, mesh);
		new Drawable(mesh);
		this->game_objects_.push_back(mesh);
		return mesh;
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
