#include "point.hpp"

namespace game{

	PointLight::PointLight() : PointLight(1.0, glm::vec3(1.f, 1.f, 1.f)){}

	PointLight::PointLight(float power) : PointLight(power, glm::vec3(1.f, 1.f, 1.f)){}

	PointLight::PointLight(float p, glm::vec3 c){
		power = p;
		color = c;
	}

}
