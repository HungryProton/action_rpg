#include "entity_factory.hpp"
#include "entity/entity.hpp"
#include "component/transform.hpp"

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
	}

	void EntityFactory::RegisterPreset(std::string preset_name, unsigned long entity){
		auto it = presets_.find(preset_name);
		if(it != presets_.end()){
			LOG(WARNING) << "Preset " << preset_name << " is already registered."
				<< "Request ignored" << std::endl;
			return;
		}
		presets_.insert(std::make_pair(preset_name, entity));
	}

	void EntityFactory::GeneratePlayerPreset(){
		unsigned long player = Entity::Create();
		new Transform(player);
		RegisterPreset("player", player);
	}

	void EntityFactory::GenerateRockPreset(){
		unsigned long rock = Entity::Create();
		new Transform(rock);
		RegisterPreset("rock", rock);
	}

	std::map<std::string, unsigned long> EntityFactory::presets_;
}
