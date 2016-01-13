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
		// Check if preset is present
		auto preset = this->presets_.find(name);
		if(preset == this->presets_.end())
			return nullptr;

		// if present, return the preset
		GameObject* template_game_object = preset->second;
		if(template_game_object){
			return template_game_object->Clone();
		}

		// Erase preset if pointer became invalid
		this->presets_.erase(preset);
		return nullptr;
	}

	void GameObjectBuilder::RegisterPreset(std::string name, GameObject* object){
		// Check if preset has been registered
		auto preset = this->presets_.find(name);
		if(preset != this->presets_.end()){
			// Check is preset is valid
			if(preset->second){
				LOG(WARNING) << "The preset " << name << " is already registered." <<
				" It can not be saved again." << std::endl;
				return;
			}
			// Erase invalid preset otherwise and register the new preset
			this->presets_.erase(preset);
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
