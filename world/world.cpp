#include "world.hpp"

#include "ecs/entity.hpp"
#include "ecs/entity_factory.hpp"
#include "component/transform.hpp"

namespace game{

	void World::GenerateNew(){
		EntityFactory::LoadInitialPresets();
		entity_generator_.SpawnPlayer();
		//EntityFactory::CreateFromPreset("rock");
		unsigned long camera = entity_generator_.SpawnCamera();
		Transform* t = Entity::GetComponent<Transform>(camera);
		t->position = glm::vec3(0, -8, 7);

		for(int i = 0; i < 500; i++){
			entity_generator_.SpawnRandom();
		}
	}

	void World::LoadFromFile(){

	}

	void World::SaveToFile(){

	}

	EntityGenerator World::entity_generator_;
}
