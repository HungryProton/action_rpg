#ifndef GAME_SYSTEM_RENDERER_CAMERA_CONTROLLER_HPP_
#define GAME_SYSTEM_RENDERER_CAMERA_CONTROLLER_HPP_

#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/rendering_intent.hpp"

namespace game{

	class CameraController : public MessageHandler<RenderingIntent>{
		public:
			CameraController();
			~CameraController();

			unsigned long GetCamera();
			glm::mat4 GetView();
			glm::mat4 GetProjection();
			void Update();

		protected:
			void OnMessage(RenderingIntent);
			void SetActiveCamera(unsigned long);

		private:
			unsigned long camera_;
			glm::mat4 view_;
			glm::mat4 projection_;
	};
}

#endif //GAME_SYSTEM_RENDERER_CAMERA_CONTROLLER_HPP_
