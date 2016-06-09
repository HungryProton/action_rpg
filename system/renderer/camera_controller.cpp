#include "camera_controller.hpp"
#include "entity/entity.hpp"
#include "component/camera.hpp"
#include "component/transform.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"

namespace game{

	CameraController::CameraController() : MessageHandler<RenderingIntent>(){ }

	CameraController::~CameraController(){ }

	void CameraController::Update(){
		this->MessageHandler<RenderingIntent>::PollMessages();
		Transform* transform = Entity::GetComponent<Transform>(camera_);
		Camera* camera = Entity::GetComponent<Camera>(camera_);
		if(!transform || !camera){ return; }

		camera->view = glm::lookAt(transform->position,
															 camera->target,
															 camera->up );
		view_ = camera->view;
		projection_ = camera->projection;
	}

	void CameraController::SetActiveCamera(unsigned long new_camera){
		camera_ = new_camera;
	}

	glm::mat4 CameraController::GetView(){
		return view_;
	}

	glm::mat4 CameraController::GetProjection(){
		return projection_;
	}

	void CameraController::OnMessage(RenderingIntent msg){
		switch(msg.action){
			case RIntent::SET_ACTIVE_CAMERA:
				SetActiveCamera(msg.from_id);
				break;

			case RIntent::NONE:
			default:
				break;
		}
	}
}
