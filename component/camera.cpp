#include "camera.hpp"
#include "messaging/message_bus.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "ecs/entity.hpp"

namespace game{

	Camera::Camera() : Component(){
		this->active = false;
		this->up = glm::vec3(0,0,1);
		this->target = glm::vec3(0,0,0);
		this->znear = 1.f;
		this->zfar = 100.f;
		this->ratio = 1366.f/768.f;
		this->fovy = 0.520f;
		this->projection = glm::perspective(fovy, ratio, znear, zfar);
	}

	Camera::~Camera(){}

	Camera::Camera(Entity entity) : Camera(){
		Entity::AttachComponent<Camera>(entity, this);
	}

	Camera::Camera(Camera* camera) : Camera(){
		this->projection = camera->projection;
		this->view = camera->view;
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

	void Camera::SetActive(){
		RenderingIntent intent;
		intent.action = RIntent::SET_ACTIVE_CAMERA;
		intent.from_id = this->parent;
		MessageBus::Push(intent);
		active = true;
	}
}
