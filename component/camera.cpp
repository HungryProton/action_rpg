#include "camera.hpp"
#include "messaging/message_bus.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"
#include "ecs/ecs.hpp"

namespace game{

	Camera::Camera(){
		this->active = false;
		this->up = glm::vec3(0,0,1);
		this->target = glm::vec3(0,0,0);
		this->znear = 1.f;
		this->zfar = 100.f;
		this->ratio = 1366.f/768.f;
		this->fovy = 0.520f;
		this->projection = glm::perspective(fovy, ratio, znear, zfar);
		this->parent = ecs::GetParentOf(this);
	}

	void Camera::SetActive(){
		RenderingIntent intent;
		intent.action = RIntent::SET_ACTIVE_CAMERA;
		intent.from = this->parent;
		MessageBus::Push(intent);
		active = true;
	}
}
