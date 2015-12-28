#include "camera.hpp"
#include "core/messaging/message_bus.hpp"
#include "core/messaging/concrete_messages/rendering_intent.hpp"

namespace game{

	Camera::Camera() : Camera((GameObject*)nullptr){

	}

	Camera::Camera(GameObject* p) : Component(p){
		this->active = true;
		this->up = glm::vec3(0,0,1);
		this->target = glm::vec3(0,0,0);
		RenderingIntent intent;
		intent.action = RI_ACTIVE_CAMERA;
		intent.game_object = p;
		MessageBus::Push(intent);
	}

	Camera::Camera(Camera* camera){
		this->view_projection = camera->view_projection;
		this->znear = camera->znear;
		this->zfar = camera->zfar;
		this->ratio = camera->ratio;
		this->fovy = camera->fovy;
		this->target = camera->target;
		this->up = camera->up;
	}

	Camera* Camera::Clone(){
		return new Camera(this);
	}
}
