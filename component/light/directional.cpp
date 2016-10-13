#include "directional.hpp"

namespace game{

	DirectionalLight::DirectionalLight(){
		direction = glm::vec3(0, 0, -1);
		color = glm::vec3(1, 1, 1);
		power = 1;
	}

	DirectionalLight::DirectionalLight(glm::vec3 d, float p) : DirectionalLight(){
		direction = d;
		power = p;
	}

	DirectionalLight::DirectionalLight(glm::vec3 d, float p, glm::vec3 c){
		direction = d;
		power = p;
		color = c;
	}
}
