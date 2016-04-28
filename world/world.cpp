#include "world.hpp"

namespace game{

	void World::GenerateNew(){
		entity_generator_.SpawnPlayer();
	}

	void World::LoadFromFile(){

	}

	void World::SaveToFile(){

	}

	EntityGenerator World::entity_generator_;
}
