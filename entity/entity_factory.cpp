#include "entity_factory.hpp"
#include "entity/entity.hpp"
#include "component/transform.hpp"
#include "component/texture.hpp"
#include "component/camera.hpp"

namespace game{

	unsigned long EntityFactory::CreateFromPreset(std::string preset_name){
		auto it = presets_.find(preset_name);
		if(it == presets_.end()){
			LOG(WARNING) << "Requested preset " << preset_name << " wasn't found" << std::endl;
			return 0;
		}

		return Entity::Clone(it->second);
	}

	void EntityFactory::LoadInitialPresets(){
		GeneratePlayerPreset();
		GenerateRockPreset();
		GenerateCameraPreset();
	}

	void EntityFactory::RegisterPreset(std::string preset_name, unsigned long entity){
		auto it = presets_.find(preset_name);
		if(it != presets_.end()){
			LOG(WARNING) << "Preset " << preset_name << " is already registered."
				<< "Request ignored" << std::endl;
			return;
		}
		LOG(DEBUG) << "Creating preset " << preset_name << std::endl;
		presets_.insert(std::make_pair(preset_name, entity));
	}

	void EntityFactory::GeneratePlayerPreset(){
		unsigned long player = Entity::Create();
		new Transform(player);
		new Texture("../data/characters/female/single.png", player);
		RegisterPreset("player", player);
	}

	void EntityFactory::GenerateRockPreset(){
		unsigned long rock = Entity::Create();
		new Transform(rock);
		RegisterPreset("rock", rock);
	}

	void EntityFactory::GenerateCameraPreset(){
		unsigned long camera = Entity::Create();
		new Transform(camera);
		new Camera(camera);
		RegisterPreset("camera", camera);
	}

	std::map<std::string, unsigned long> EntityFactory::presets_;
}
