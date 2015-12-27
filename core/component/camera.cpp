#include "camera.hpp"

namespace game{

	Camera::Camera() : Component(){

	}

	Camera::Camera(GameObject* p) : Component(p){

	}

	Camera::Camera(Camera* camera){
		this->view = camera->view;
		this->projection = camera->projection;
	}

	Camera* Camera::Clone(){
		return new Camera(this);
	}
}
