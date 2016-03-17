#include "utils.hpp"
#include "core/component/transform.hpp"
#include "glm.hpp"

namespace game{

	float Utils::Distance(GameObject* a, GameObject* b){
		Transform* t1 = a->GetComponent<Transform>();
		Transform* t2 = b->GetComponent<Transform>();

		if(!t1 || !t2){ return -1; }

		return glm::distance(t1->position, t2->position);

	}
}
