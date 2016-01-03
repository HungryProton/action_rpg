#include "logic.hpp"
#include "core/locator/locator.hpp"
#include "core/service/builder/world_builder.hpp"
#include "core/service/builder/game_object_builder.hpp"
#include "core/game/game.hpp"

#include "core/component/component_list.hpp"

namespace game{

	Logic::Logic(){
		Game::RequestForService<WorldBuilder>();
		Game::RequestForService<GameObjectBuilder>();
	}

	Logic::~Logic(){
		this->ClearMemory();
	}

	void Logic::Initialize(){
		WorldBuilder* world_builder = Locator::Get<WorldBuilder>();

		SpawnSprite("../data/characters/female/female_1.png");
		SpawnCamera(glm::vec3(-2, -2, 2));

	}

	void Logic::ClearMemory(){
		for(unsigned int i = 0; i < this->game_objects_.size(); i++){
			GameObject* g = this->game_objects_[i];
			this->game_objects_.erase(this->game_objects_.begin() + i);
			delete g;
		}
	}

	void Logic::Update(){
		for(auto it = this->game_objects_.begin();
				it != this->game_objects_.end();
				it++){
			(*it)->Update();
		}
	}

	GameObject* Logic::SpawnSprite(std::string file_path){
		GameObject* sprite = new GameObject();
		new Transform(sprite);
		new Texture(file_path, sprite);
		new Drawable(sprite);
		return sprite;
	}

	GameObject* Logic::SpawnCamera(glm::vec3 position){
		GameObject* camera = new GameObject();
		Transform* t = new Transform(camera);
		t->position = position;
		new Camera(camera);
		new Motion(camera);
		new InputToMotion(camera);
		return camera;
	}
}
