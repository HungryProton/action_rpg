#include "world.hpp"

#include "entity/entity.hpp"
#include "entity/entity_factory.hpp"
#include "component/transform.hpp"

namespace game{

	void World::GenerateNew(){
		EntityFactory::LoadInitialPresets();
		entity_generator_.SpawnPlayer();
		unsigned long camera = entity_generator_.SpawnCamera();
		Transform* t = Entity::GetComponent<Transform>(camera);
		t->position = glm::vec3(0, -5, 5);
	}

	void World::LoadFromFile(){

	}

	void World::SaveToFile(){

	}

	EntityGenerator World::entity_generator_;
}
