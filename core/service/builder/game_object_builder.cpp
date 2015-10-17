#include "tools/logger.hpp"
#include "game_object_builder.hpp"

namespace game{

	GameObjectBuilder::GameObjectBuilder(){

	}

	GameObjectBuilder::~GameObjectBuilder(){
		this->ClearMemory();
	}

	GameObject* GameObjectBuilder::CreateBlank(){
		return new GameObject();
	}

	GameObject* GameObjectBuilder::CreateFromPreset(std::string name){
		auto preset = this->presets_.find(name);
		if(preset == this->presets_.end())
			return nullptr;

		GameObject* template_game_object = preset->second;
		return template_game_object->Clone();
	}

	void GameObjectBuilder::RegisterPreset(std::string name, GameObject* object){
		auto preset = this->presets_.find(name);
		if(preset != this->presets_.end()){
			LOG(WARNING) << "The preset " << name << " is already registered.";
			LOG(WARNING) << "The new preset will not be saved." << std::endl;
			return;
		}
		this->presets_.insert(std::pair<std::string, GameObject*>(name, object));
	}

	void GameObjectBuilder::ClearMemory(){
		auto it = this->presets_.begin();

		while(it != this->presets_.end()){
			auto it2 = it;
			it++;
			delete it2->second;
		}
		this->presets_.clear();
	}
}
